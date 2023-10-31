/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:18:44 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/29 22:50:34 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*List utils*/
t_quotes	*quotenew(char *content, int status, unsigned long len)
{
	t_quotes	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->sequence = ft_strndup(content, len);
	if (!new->sequence)
		return (free(new), NULL);
	new->status = status;
	new->next = NULL;
	return (new);
}

void	quoteadd_back(t_quotes **lst, t_quotes *new_node)
{
	t_quotes	*current;

	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

void	opadd_back(t_op **lst, t_op *new_node)
{
	t_op	*current;

	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

t_op	*opnew(char *content, int status, int op, unsigned long len)
{
	t_op	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->sequence = ft_strndup(content, len);
	if (!new->sequence)
		return (free(new), NULL);
	new->special_character = op;
	new->status = status;
	new->next = NULL;
	return (new);
}
