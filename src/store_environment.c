/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:53:52 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/31 21:34:36 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*envnew(char *name, char *content, unsigned long len)
{
	t_env	*new;

	if (!name)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->name = name;
	new->line = ft_strndup(content, len);
	if (!new->line)
		return (free(new), NULL);
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

void	print_env(t_shell *data)
{
	t_env	*head;

	head = *data->env_list;
	while (head)
	{
		printf("NAME: %s\nLINE: %s\n------\n", head->name, head->line);
		head = head->next;
	}
}

int	get_environment(t_shell *data)
{
	char	**t;
	size_t	i;
	t_env	*new;

	i = 0;
	t = data->environment;
	while (*t)
	{
		i = 0;
		while (**t != '=')
		{
			*t += 1;
			i++;
			if (**t == '=')
			{
				new = envnew(ft_strndup(*t - i, i), *t + 1, ft_strlen(*t + 1));
				if (!new)
					return (-1);
				envadd_back(data->env_list, new);
			}
		}
		t++;
	}
	return (0);
}
