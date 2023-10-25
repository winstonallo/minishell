/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/25 14:11:03 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	expand_sequences(data);
	remove_escape(data);
	parse_special_char(data);
	get_command_table(data);
	print_cmd_tables(data->cmd_table);
	status = find_command(data->raw_input, data);
	if (status == COMMAND_NOT_FOUND)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(data->raw_input, 2);
	}
	wipe(data);
	if (status == EXIT)
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
		if (initialize_sequences(data) == -1)
			return (-1);
		data->raw_input = readline("\033[0;35m\033[1mminishell \033[0;30m");
		if (!data->raw_input)
			return (-1);
		add_history(data->raw_input);
		parse_for_quotes(data);
		expand_sequences(data);
		remove_escape(data);
		parse_special_char(data);
		get_command_table(data);
		print_cmd_tables(data->cmd_table);
		status = find_command(data->raw_input, data);
		if (status == COMMAND_NOT_FOUND)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(data->raw_input, 2);
		}
		wipe(data);
		if (status == EXIT)
			return (EXIT);
	}
	return (0);
}
