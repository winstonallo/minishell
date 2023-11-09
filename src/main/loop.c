/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 13:54:15 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "clear_terminal" clears the terminal screen by executing the 
 * "clear" command.
 */
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

/**
 * The function reads user input, processes it for quotes, expands sequences, 
 * parses special characters, creates a command table, 
 * and finds the command to execute.
 */
int	read_input(t_shell *data)
{
	add_history(data->raw_input);
	if (parse_for_quotes(data) == -1)
		return (-1);
	if (expand_sequences(data) == -1)
		return (-1);
	if (parse_special_char(data) == -1)
		return (-1);
	if (get_command_table(data) == -1)
		return (-1);
	data->exit = find_command(data);
	return (0);
}

/**
 * The function "check_status" checks the exit status of a shell command 
 * and returns the appropriate value.
 * @return the value of `data->exit`.
 */
int	check_status(t_shell *data)
{
	if (data->exit == COMMAND_NOT_FOUND)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(data->raw_input, 2);
		return (COMMAND_NOT_FOUND);
	}
	else if (data->exit == EXIT)
		return (EXIT);
	return (data->exit);
}

/**
 * The function `first_read` reads user input, processes it, and 
 * returns the exit status.
 * Extra function for the first readline call in order to clear 
 * the terminal on startup
 * @return the value of `data->exit`.
 */
int	first_read(t_shell *data)
{
	clear_terminal(data->environment);
	get_prompt(data, 0);
	data->raw_input = readline(data->prompt);
	if (!data->raw_input)
		return (data->exit);
	if (read_input(data) == -1)
		return (data->exit);
	data->exit = check_status(data);
	if (data->exit == EXIT)
		return (EXIT);
	wipe(data);
	return (data->exit);
}

/**
 * The function "loop" reads input from the user, processes it, and repeats 
 * the process until an exit condition is met.
 * 
 * @param data The parameter "data" is of type "t_shell", which is a struct
 *  that contains information and variables related to the shell program.
 * 
 * @return an integer value. If the condition `first_read(data) == EXIT` 
 * is true, then the function will return the value of `EXIT`. Otherwise,
 * if any of the subsequent conditions are true, the function will return 
 * the value of `data->exit`. If none of the conditions are true, the function
 * will return 0.
 */
int	loop(t_shell *data)
{
	if (first_read(data) == EXIT)
		return (EXIT);
	while (1)
	{
		if (initialize_sequences(data) == -1)
			return (data->exit);
		data->raw_input = readline(data->prompt);
		if (!data->raw_input)
			return (data->exit);
		if (read_input(data) == -1)
			return (data->exit);
		if (check_status(data) == EXIT)
			return (EXIT);
		wipe(data);
	}
	return (0);
}
