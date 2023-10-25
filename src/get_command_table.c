/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:14:45 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/25 17:41:27 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧*/

char	**get_command_array(t_op *data)
{
	t_op	*head;
	int		i;
	char	**arr;

	i = 0;
	head = data;
	while (++i && head && head->special_character != PIPE)
		head = head->next;
	arr = malloc((i + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (data && data->special_character != PIPE)
	{
		if ((data->special_character == OUTPUT_REDIRECTION
				|| data->special_character == INPUT_REDIRECTION))
			data = data->next;
		arr[i] = ft_strdup(data->sequence);
		if (!arr[i])
			return (free_array(arr), NULL);
		data = data->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

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
		if (h->special_character == OUTPUT_REDIRECTION)
			out = open(h->next->sequence, O_CREAT | O_TRUNC | O_RDWR, 0000644);
		else if (h->special_character == INPUT_REDIRECTION)
			in = open(h->next->sequence, O_RDONLY);
		h = h->next;
	}
	new = cmdnew(out, in, 0);
	if (!new)
		return (close(in), close(out), -1);
	cmdadd_back(cmd_table, new);
	return (0);
}

int	add_delimiter(t_shell *data)
{
	t_cmd_table	*new;

	new = cmdnew(NO_FD, NO_FD, PIPE);
	if (!new)
		return (-1);
	cmdadd_back(data->cmd_table, new);
	return (0);
}

int	get_command_table(t_shell *data)
{
	t_op	*op_head;

	op_head = *data->operators;
	while (op_head)
	{
		if (initialize_redirections(op_head, data->cmd_table) == -1)
			return (-1);
		data->cmd_head = *data->cmd_table;
		while (data->cmd_head->args || data->cmd_head->pipe == PIPE)
			data->cmd_head = data->cmd_head->next;
		data->cmd_head->args = get_command_array(op_head);
		if (!data->cmd_head->args)
			return (-1);
		while (op_head && op_head->special_character != PIPE)
			op_head = op_head->next;
		if (op_head && op_head->special_character == PIPE)
		{
			if (add_delimiter(data) == -1)
				return (-1);
			op_head = op_head->next;
		}
		while (data->cmd_head)
			data->cmd_head = data->cmd_head->next;
	}
	return (0);
}
