/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special_characters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:35:55 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/05 17:54:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Here we go through the whole list again and look for special characters like
PIPE('|'), OUTPUT REDIRECTION('>') and INPUT REDIRECTION('<').
This is tricky because they do not have to be separated by spaces from other
command line arguments.
We re-split the sequences, make extra nodes in the list for special
characters and set the flags accordingly*/
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

/*Look for special characters in the string, and split it
accordingly, setting the special character flag.*/
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
					return (free_opps(data->operators), data->exit);
			}
		}
		if (isop(seq[j]))
		{
			if (add_node_special_char(NULL, 0, data, isop(seq[j])) == -1)
				return (free_opps(data->operators), data->exit);
			j++;
		}
	}
	return (data->exit);
}

/*Go through the list and look for special characters in each sequence*/
int	parse_special_char(t_shell *data)
{
	t_quotes	*temp;

	temp = *data->sequences;
	while (temp)
	{
		if (split_curr_sequence(temp->sequence, data) == -1)
			return (data->exit);
		temp = temp->next;
	}
	return (data->exit);
}
