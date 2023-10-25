/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:14:45 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/25 14:15:03 by abied-ch         ###   ########.fr       */
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

	while (head && !head->special_character)
	{
		i++;
		head = head->next;
	}
	arr = malloc((i + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (data && data->special_character != PIPE)
	{
		if ((data->special_character == OUTPUT_REDIRECTION || data->special_character == INPUT_REDIRECTION))
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

int	get_command_table(t_shell *data)
{
	t_cmd_table	*cmd_table;
	t_op		*head;
	t_cmd_table	*new;
	
	data->cmd_table = malloc(sizeof(data->cmd_table));
	if (!data->cmd_table)
		return (-1);
	*data->cmd_table = NULL;
	cmd_table = NULL;
	head = *data->operators;
	while (head)
	{
		if (initialize_redirections(head, data->cmd_table) == -1)
			return (-1);
		cmd_table = *data->cmd_table;
		while (cmd_table->args || cmd_table->pipe == PIPE)
			cmd_table = cmd_table->next;
		cmd_table->args = get_command_array(head);
		if (!cmd_table->args)
			return (-1);
		while (head && head->special_character != PIPE)
			head = head->next;
		if (head && head->special_character == PIPE)
		{
			new = cmdnew(NO_FD, NO_FD, PIPE);
			if (!new)
				return (-1);
			cmdadd_back(data->cmd_table, new);
			head = head->next;
		}
		while (cmd_table)
			cmd_table = cmd_table->next;
	}
	return (0);	
}
