/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_special_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:47:59 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 15:50:06 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	new->s_char = op;
	new->status = status;
	new->next = NULL;
	return (new);
}

void	free_opps(t_op **opps)
{
	t_op	*current;
	t_op	*next;

	if (*opps)
	{
		current = *opps;
		while (current)
		{
			next = current->next;
			free(current->sequence);
			free(current);
			current = next;
		}
	}
	free(opps);
}
