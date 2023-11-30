/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:25:49 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 08:42:13 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_dox	*doxnew(char *content)
{
	t_dox	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->name = content;
	new->next = NULL;
	return (new);
}

int	doxadd_back(t_dox **lst, t_dox *new_node)
{
	t_dox	*current;

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

void	free_dox(t_dox **stack_a)
{
	t_dox	*temp;
	t_dox	*current;

	if (!stack_a)
		return ;
	if (!*stack_a)
		return (freeze(stack_a));
	current = *stack_a;
	while (current)
	{
		temp = current->next;
		if (current->name)
		{
			unlink(current->name);
			freeze(current->name);
		}
		freeze(current);
		current = temp;
	}
	freeze(stack_a);
}
