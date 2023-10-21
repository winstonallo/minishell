/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sequences.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:41:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/21 21:35:05 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_dquotes(t_quotes *current)
{
	size_t	i;
	char	*new;
	char	*expanded_content;
	char	*temp;

	expanded_content = "Expanded Content";
	i = 0;
	new = NULL;
	while (current->sequence[i])
	{
		if (current->sequence[i] == '$')
		{
			temp = ft_strndup(current->sequence, i);
			if (!temp)
				return (NULL);
			while (current->sequence[i] && !myisspace(current->sequence[i]))
				i++;
			new = ft_strjoin(temp, expanded_content);
			if (!new)
				return (free(temp), NULL);
			free(temp);
		}
		else
			i++;
	}
	if (!new)
		return (current->sequence);
	free(current->sequence);
	return (new);
}

void	expand_sequences(t_shell *data)
{
	t_quotes	*head;

	head = *data->sequences;
	while (head)
	{
		if (head->status == IN_DOUBLE_QUOTES)
			head->sequence = expand_dquotes(head);
		printf("%s\n", head->sequence);
		head = head->next;
	}
}
