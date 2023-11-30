/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 08:43:50 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredocs(t_shell *data)
{
	t_cmd_table	*head;
	int			id;

	free_dox(data->dox);
	data->dox = malloc(sizeof(t_dox **));
	if (!data->dox)
		return (-1);
	*data->dox = NULL;
	head = *data->cmd_table;
	id = 0;
	while (head)
	{
		if (head->heredoc)
			heredoc(head, data, id);
		head = head->next;
		id++;
	}
	return (0);
}

/**
 * The function reads user input, processes it for quotes, expands sequences, 
 * parses special characters, creates a command table, 
 * and finds the command to execute.
 */
int	read_input(t_shell *data)
{
	add_history(data->raw_input);
	if (tokenize(data) == -1)
		return (-1);
	if (expand(data) == -1)
		return (-1);
	if (parse_special_char(data) == -1)
		return (-1);
	if (merge_args(data) == -1)
		return (-1);
	if (lexer(data) == -1)
		return (-1);
	if (get_command_table(data) == -1)
		return (-1);
	checkcmd(data);
	heredocs(data);
	if (!data->builtin_executed)
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
	if (data->exit == EXIT)
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
		listen(data, INTERACTIVE);
		data->raw_input = readline(data->prompt);
		listen(data, NON_INTERACTIVE);
		if (g_sig == CTRL_C)
			data->exit = 130;
		if (!data->raw_input)
			return (myexit(data));
		if (!data->raw_input[0] && wipe(data))
			continue ;
		if (read_input(data) == -1 && wipe(data))
			continue ;
		if (check_status(data) == EXIT)
			return (EXIT);
		wipe(data);
	}
	return (0);
}
