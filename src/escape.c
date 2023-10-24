/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:54:51 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 15:28:32 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*remove_backslash(char *seq, int size)
{
	char	*new;
	int		i;
	int		j;

	new = malloc((size + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (seq[i])
	{
		if (seq[i] == '\\')
			i++;
		new[j] = seq[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (free(seq), new);
}

static char	*escape(char *seq)
{
	int		size;
	int		i;
	char	*new;

	size = 0;
	i = 0;
	while (seq[i])
	{
		if (seq[i] == '\\')
		{
			i++;
			if (!seq[i])
				break ;
		}
		size++;
		i++;
	}
	new = remove_backslash(seq, size);
	if (!new)
		return (NULL);
	return (new);
}

int	remove_escape(t_shell *data)
{
	t_quotes	*head;

	head = *data->sequences;
	while (head)
	{
		if (head->status == UNQUOTED || head->status == IN_DOUBLE_QUOTES)
		{
			head->sequence = escape(head->sequence);
			if (!head->sequence)
				return (-1);
		}
		printf("%s\n", head->sequence);
		head = head->next;
	}
	return (0);
}
