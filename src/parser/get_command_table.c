/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:14:45 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 15:32:25 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Here we rearrange the list one (hopefully last) time, we look for PIPE 
characters or the end of the list as command table delimiters 
(one command table is either until the end of the line or until the next pipe),
and put them into char **arrays in order to be able to pass them to execve.
We also look for input/output redirections, open the files into the list's
file descriptor and remove them from the list.*/
char	**get_command_array(t_op *data, int i, int j)
{
	t_op	*head;
	char	**arr;

	head = data;
	while (++i && head && head->special_character != PIPE)
		head = head->next;
	arr = malloc((i + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (data && data->special_character != PIPE)
	{
		if ((data->special_character == OUT_REDIR
				|| data->special_character == IN_REDIR))
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

/*Look for redirections, open the according files, store FDs to the command
table*/
int	initialize_redirections(t_op *data, t_cmd_table **cmd_table)
{
	t_op		*h;
	t_cmd_table	*new;
	int			in;
	int			out;

	h = data;
	in = NO_FD;
	out = NO_FD;
	while (h && h->special_character != PIPE)
	{
		if (h->special_character == OUT_REDIR && h->status == UNQUOTED)
			out = open(h->next->sequence, O_CREAT | O_TRUNC | O_RDWR, 0000644);
		else if (h->special_character == IN_REDIR && h->status == UNQUOTED)
			in = open(h->next->sequence, O_RDONLY);
		h = h->next;
	}
	new = cmdnew(out, in, 0);
	if (!new)
		return (close(in), close(out), -1);
	cmdadd_back(cmd_table, new);
	return (0);
}

/*Lines saving util function, creates a new delimiter node and
adds it to the list*/
int	add_delimiter(t_shell *data)
{
	t_cmd_table	*new;

	new = cmdnew(NO_FD, NO_FD, PIPE);
	if (!new)
		return (-1);
	cmdadd_back(data->cmd_table, new);
	return (0);
}

/*
1. Look for redirection characters, open the files and skip them so
they are not stored in the arguments array
2. Move the head of the list until we find either:
EITHER a pipe (which signalizes the start of another command table)
OR the end of the list, which means we are either done or we need to
get the next command table
3. Make a new node out of the arguments that we found until the next
delimiter
4. If we found a pipe, add a delimiter to the command table list
5. Repeat until the end of the list
*/

int	get_command_table(t_shell *data)
{
	t_op	*op_head;

	op_head = *data->operators;
	while (op_head)
	{
		if (initialize_redirections(op_head, data->cmd_table) == -1)
			return (data->exit);
		data->cmd_head = *data->cmd_table;
		while (data->cmd_head->args || data->cmd_head->pipe == PIPE)
			data->cmd_head = data->cmd_head->next;
		data->cmd_head->args = get_command_array(op_head, 0, -1);
		if (!data->cmd_head->args)
			return (data->exit);
		while (op_head && op_head->special_character != PIPE)
			op_head = op_head->next;
		if (op_head && op_head->special_character == PIPE)
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
