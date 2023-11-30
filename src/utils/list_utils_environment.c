/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_environment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:53:52 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 10:37:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	envsize(t_env **list)
{
	t_env	*head;
	int		i;

	i = 0;
	head = *list;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

t_env	*envnew(char *name, char *content, unsigned long len)
{
	t_env	*new;

	if (!name)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (free(name), NULL);
	new->name = name;
	new->line = ft_strndup(content, len);
	if (!new->line)
		return (free(new), free(name), NULL);
	new->next = NULL;
	return (new);
}

void	envadd_back(t_env **lst, t_env *new_node)
{
	t_env	*current;

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

void	free_environment(t_env **env)
{
	t_env	*head;
	t_env	*temp;

	head = *env;
	while (head)
	{
		temp = head;
		if (temp->line)
			freeze(temp->line);
		if (temp->name)
			freeze(temp->name);
		head = head->next;
		freeze(temp);
	}
	freeze(env);
}
