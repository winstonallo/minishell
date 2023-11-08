/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special_characters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:35:55 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 21:50:08 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stddef.h>

/*Here we go through the whole list again and look for special characters like
PIPE('|'), OUTPUT REDIRECTION('>') and INPUT REDIRECTION('<').
This is tricky because they do not have to be separated by spaces from other
command line arguments.
We re-split the sequences, make extra nodes in the list for special
characters and set the flags accordingly*/
int	isop(char *s, size_t *j, t_shell *data)
{
	if (*s == '|' && !data->s_char_tmp)
			data->s_char_tmp = PIPE;
	else if (*s == '<' && *(s + 1) != '<' && !data->s_char_tmp)
		data->s_char_tmp = IN_REDIR;
	else if (*s == '>' && *(s + 1) != '>' && !data->s_char_tmp)
		data->s_char_tmp = OUT_REDIR;
	else if (*s == '>' && *(s + 1) == '>' && !data->s_char_tmp)
	{
		*j += 1;
		data->s_char_tmp = APPEND;
	}
	else if (*s == '<' && *(s + 1) == '<' && !data->s_char_tmp)
	{
		*j += 1;
		data->s_char_tmp = HEREDOC;
	}
	if (data->s_char_tmp)
		return (1);
	return (0);
}

int	add_node_special_char(char *seq, size_t len, t_shell *data, int status)
{
	t_op	*new;

	new = opnew(seq, UNQUOTED, status, len);
	if (!new)
		return (-1);
	opadd_back(data->operators, new);
	data->s_char_tmp = 0;
	return (0);
}

/*Look for special characters in the string, and split it
accordingly, setting the special character flag.*/
int	split_curr_sequence(char *seq, t_shell *d)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (seq && seq[++i] && seq[j])
	{
		i = j;
		while (!isop(&seq[j], &j, d) && seq[j])
		{
			j++;
			if ((isop(&seq[j], &j, d) || !seq[j]))
			{
				if (add_node_special_char(&seq[i], j - i, d, 0) == -1)
					return (free_opps(d->operators), d->exit);
			}
		}
		if (isop(&seq[j], &j, d))
		{
			if (add_node_special_char(NULL, 0, d, d->s_char_tmp) == -1)
				return (free_opps(d->operators), d->exit);
			j++;
		}
	}
	return (d->exit);
}

/*Go through the list and look for special characters in each sequence*/
int	parse_special_char(t_shell *data)
{
	t_quotes	*t;
	t_op		*new;

	t = *data->sequences;
	while (t)
	{
		if (t->status == UNQUOTED)
		{
			if (split_curr_sequence(t->sequence, data) == -1)
				return (data->exit);
		}
		else
		{
			new = opnew(t->sequence, t->status, 0, ft_strlen(t->sequence));
			if (!new)
				return (-1);
			opadd_back(data->operators, new);
		}
		t = t->next;
	}
	return (data->exit);
}
