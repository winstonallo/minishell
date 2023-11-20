/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/20 19:19:06 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (expand(data) == -1)
		return (-1);
	if (parse_special_char(data) == -1)
		return (-1);
	if (lexer(data) == -1)
		return (-1);
	if (get_command_table(data) == -1)
		return (-1);
	if (checkcmd(data) != COMMAND_NOT_FOUND)
		return (SUCCESS);
	execute_command(data);
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
		ft_putstr_fd(data->raw_input, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (COMMAND_NOT_FOUND);
	}
	else if (data->exit == EXIT)
		return (EXIT);
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
	while (1)
	{
		if (initialize_sequences(data) == -1)
			return (data->exit);
		data->raw_input = readline(data->prompt);
		if (!data->raw_input)
			return (myexit(data));
		if (!data->raw_input[0])
		{
			wipe(data);
			continue ;
		}
		if (read_input(data) == -1)
		{
			wipe(data);
			continue ;
		}
		if (check_status(data) == EXIT)
			return (EXIT);
		wipe(data);
	}
	return (0);
}
