/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_quote_parsing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:18:44 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 06:32:12 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_quotes	*quotenew(char *content, int status, unsigned long len)
{
	t_quotes	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	if (content)
	{
		new->sequence = ft_strndup(content, len);
		if (!new->sequence)
			return (free(new), NULL);
	}
	else
		new->sequence = NULL;
	new->status = status;
	new->next = NULL;
	return (new);
}

int	quoteadd_back(t_quotes **lst, t_quotes *new_node)
{
	t_quotes	*current;

	if (!new_node)
		return (-1);
	if (*lst == NULL)
	{
		*lst = new_node;
		return (0);
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (0);
}

void	free_sequences(t_quotes **sequences)
{
	t_quotes	*current;
	t_quotes	*next;

	if (sequences && *sequences)
	{
		current = *sequences;
		while (current)
		{
			next = current->next;
			free(current->sequence);
			free(current);
			current = next;
		}
	}
	if (sequences)
		free(sequences);
}
