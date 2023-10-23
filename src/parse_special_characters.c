/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special_characters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:35:55 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/23 23:03:57 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stddef.h>

int	isop(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INPUT_REDIRECTION);
	else if (c == '>')
		return (OUTPUT_REDIRECTION);
	return (0);
}

int	add_node_special_char(char *seq, size_t len, t_shell *data, int status)
{
	t_op	*new;

	new = opnew(seq, UNQUOTED, status, len);
	if (!new)
		return (-1);
	opadd_back(data->operators, new);
	return (0);
}

int	split_curr_sequence(char *seq, t_shell *data)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (seq[++i] && seq[j])
	{
		i = j;
		while (!isop(seq[j]) && seq[j])
		{
			j++;
			if (isop(seq[j]) || !seq[j])
			{
				if (add_node_special_char(&seq[i], j - i, data, 0) == -1)
					return (free_opps(data->operators), -1);
			}
		}
		if (isop(seq[j]))
		{
			if (add_node_special_char(NULL, 0, data, isop(seq[j])) == -1)
				return (free_opps(data->operators), -1);
			j++;
		}
	}
	return (0);
}

int	parse_special_char(t_shell *data)
{
	t_quotes	*temp;

	temp = *data->sequences;
	while (temp)
	{
		if (split_curr_sequence(temp->sequence, data) == -1)
			return (-1);
		temp = temp->next;
	}
	return (0);
}
