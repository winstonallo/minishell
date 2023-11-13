/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:14:45 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/10 13:21:38 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "get_command_array" takes a linked list of commands and 
 * returns an array of strings containing the commands.
 * 
 * @param data A pointer to a linked list of type t_op. Each node in the 
 * linked list represents a command or an operator (such as PIPE).
 * @param i The parameter `i` is used as a counter to determine the size of the
 * array `arr`. It is incremented in the first while loop until it reaches the 
 * end of the linked list or encounters a node with the character `PIPE`.
 * @param j The parameter `j` in the `get_command_array` function is used as an
 * index to keep track of the current position in the `arr` array. 
 * It is incremented each time a new command is added to the array.
 * 
 * @return a pointer to a character array (char **)
 */
char	**get_command_array(t_op *data, int i, int j)
{
	t_op	*head;
	char	**arr;

	head = data;
	while (++i && head && head->s_char != PIPE)
		head = head->next;
	arr = malloc((i + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (data && data->s_char != PIPE)
	{
		if ((data->s_char))
		{
			if (!data->next->next)
				break ;
			data = data->next->next;
		}
		arr[++j] = ft_strdup(data->sequence);
		if (!arr[j])
			return (free_array(arr), NULL);
		data = data->next;
	}
	arr[++j] = NULL;
	return (arr);
}

/**
 * The function initializes file redirections for a command table.
 * 
 * @param data A pointer to a linked list of t_op structures. Each t_op 
 * structure represents a command or operator in a shell command line.
 * @param cmd_table A pointer to a pointer to a struct t_cmd_table. 
 * This is a table that stores information about the commands and their 
 * redirections.
 * 
 * @return an integer value. If the function is successful, it returns 0. 
 * If there is an error, it returns -1.
 */
int	initialize_redirections(t_op *data, t_cmd_table **cmd_table, int o, int i)
{
	t_op		*h;
	t_cmd_table	*new;

	h = data;
	while (h && h->s_char != PIPE)
	{
		if (h->s_char == OUT_REDIR && h->status == UNQUOTED)
			o = open(h->next->sequence, O_CREAT | O_TRUNC | O_RDWR, 0000644);
		else if (h->s_char == APPEND && h->status == UNQUOTED)
			o = open(h->next->sequence, O_CREAT | O_APPEND | O_RDWR, 0000644);
		else if (h->s_char == IN_REDIR && h->status == UNQUOTED)
			i = open(h->next->sequence, O_RDONLY);
		h = h->next;
	}
	new = cmdnew(o, i, 0);
	if (!new)
		return (close(i), close(o), -1);
	cmdadd_back(cmd_table, new);
	return (0);
}

/**
 * The function "add_delimiter" adds a new command table entry with a 
 * pipe delimiter to the given shell data structure.
 * 
 * @param data The parameter "data" is of type "t_shell*", which is a 
 * pointer to a structure of type "t_shell".
 * 
 * @return an integer value. If the value is -1, it indicates an error 
 * occurred. If the value is 0, it indicates that the function executed 
 * successfully.
 */
int	add_delimiter(t_shell *data)
{
	t_cmd_table	*new;

	new = cmdnew(NO_FD, NO_FD, PIPE);
	if (!new)
		return (-1);
	cmdadd_back(data->cmd_table, new);
	return (0);
}

/**
 * The function `get_command_table` initializes redirections and creates a 
 * command table based on the given shell data.
 * 
 * @param data A pointer to a structure of type t_shell, which contains 
 * various data related to the shell program.
 * 
 * @return the value of `data->exit`.
 */
int	get_command_table(t_shell *data)
{
	t_op	*op_head;

	op_head = *data->operators;
	while (op_head)
	{
		if (initialize_redirections(op_head, data->cmd_table, 0, 0) == -1)
			return (data->exit);
		data->cmd_head = *data->cmd_table;
		while (data->cmd_head->args || data->cmd_head->pipe == PIPE)
			data->cmd_head = data->cmd_head->next;
		data->cmd_head->args = get_command_array(op_head, 0, -1);
		if (!data->cmd_head->args)
			return (data->exit);
		while (op_head && op_head->s_char != PIPE)
			op_head = op_head->next;
		if (op_head && op_head->s_char == PIPE)
		{
			if (add_delimiter(data) == -1)
				return (data->exit);
			op_head = op_head->next;
		}
		while (data->cmd_head)
			data->cmd_head = data->cmd_head->next;
	}
	return (data->exit);
}
