/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/05 17:44:01 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*This is the main loop, it gets the input from readline, parses it and executes
it, frees everything, reinitializes the needed data and gives the prompt back.
We have one extra function for the first read, because we want to clear the
terminal on startup, but besides that it is the same as the main loop.*/
void	clear_terminal(char **env)
{
	pid_t	pid;
	char	*args[2];

	args[0] = malloc(strlen("clear") + 1);
	if (!args[0])
	{
		perror("minishell: unable to clear the terminal history");
		return ;
	}
	ft_strlcpy(args[0], "clear", 5);
	args[1] = NULL;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		execve("/usr/bin/clear", args, env);
		perror("minishell: unable to clear the terminal history");
		exit(FAILURE);
	}
	else
	{
		waitpid(0, NULL, 0);
		free(args[0]);
	}
}

/*This gets called in every loop.
Add the line from 'readline' to the command history*/
int	read_input(t_shell *data, int *status)
{
	add_history(data->raw_input);
	if (parse_for_quotes(data) == -1)
		return (data->exit = FAILURE, -1);
	if (expand_sequences(data) == -1)
		return (data->exit = FAILURE, -1);
	if (remove_escape(data) == -1)
		return (data->exit = FAILURE, -1);
	if (parse_special_char(data) == -1)
		return (data->exit = FAILURE, -1);
	if (get_command_table(data) == -1)
		return (data->exit = FAILURE, -1);
	return (*status = find_command(data));
}

int	check_status(int status, t_shell *data)
{
	if (status == COMMAND_NOT_FOUND)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(data->raw_input, 2);
	}
	else if (status == EXIT)
		return (EXIT);
	return (data->exit);
}

int	first_read(t_shell *data)
{
	int	status;

	status = 0;
	clear_terminal(data->environment);
	get_prompt(data, 0);
	data->raw_input = readline(data->prompt);
	if (!data->raw_input)
		return (data->exit);
	if (read_input(data, &status) == -1)
		return (data->exit);
	if (check_status(status, data) == EXIT)
		return (EXIT);
	wipe(data);
	return (data->exit);
}

int	loop(t_shell *data)
{
	int	status;

	if (first_read(data) == -1)
		return (data->exit = FAILURE);
	while (1)
	{
		status = 0;
		if (initialize_sequences(data) == -1)
			return (data->exit);
		data->raw_input = readline(data->prompt);
		if (!data->raw_input)
			return (data->exit);
		if (read_input(data, &status) == -1)
			return (data->exit);
		if (check_status(status, data) == EXIT)
			return (EXIT);
		wipe(data);
	}
	return (data->exit = FAILURE);
}
