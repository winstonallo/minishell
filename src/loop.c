/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/21 19:07:48 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parse_line(t_shell *data)
{
	int	i;

	i = -1;
	if (ft_strncmp(data->raw_input, "env", 4) == 0)
	{
		while (data->environment[++i])
			ft_printf("%s\n", data->environment[i]);
		return (free(data->raw_input), 0);
	}
	else if (ft_strncmp(data->raw_input, "exit", 5) == 0)
		return (free(data->raw_input), EXIT);
	return (COMMAND_NOT_FOUND);
}

void	clear_terminal(char **env)
{
	pid_t	pid;
	char	*args[2];

	args[0] = malloc(strlen("clear") + 1);
	if (!args[0])
	{
		perror("unable to clear the terminal history");
		return ;
	}
	strcpy(args[0], "clear");
	args[1] = NULL;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		execve("/usr/bin/clear", args, env);
		perror("execve");
		exit(0);
	}
	else
	{
		waitpid(0, NULL, 0);
		free(args[0]);
	}
}

int	first_read(t_shell *data)
{
	int	status;

	clear_terminal(data->environment);
	data->raw_input = readline("\033[0;35m\033[1mminishell \033[0;30m");
	if (!data->raw_input)
		return (-1);
	add_history(data->raw_input);
	parse_for_quotes(data);
	status = parse_line(data);
	if (status == COMMAND_NOT_FOUND)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(data->raw_input, 2);
		free(data->raw_input);
	}
	else if (status == EXIT)
		return (EXIT);
	return (0);
}

int	read_input(t_shell *data)
{
	int			status;

	if (first_read(data) == EXIT)
		return (EXIT);
	while (1)
	{
		data->raw_input = readline("\033[0;35m\033[1mminishell \033[0;30m");
		if (!data->raw_input)
			return (-1);
		add_history(data->raw_input);
		parse_for_quotes(data);
		status = parse_line(data);
		if (status == COMMAND_NOT_FOUND)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(data->raw_input, 2);
			free(data->raw_input);
		}
		free_sequences(data->sequences);
		if (status == EXIT)
			return (EXIT);
	}
	return (0);
}
