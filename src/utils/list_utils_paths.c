/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:00:18 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 14:05:30 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_paths(t_shell *data, char *line)
{
	if (!line[0])
		return (0);
	if (!ft_strncmp(line, "PATH", ft_strlen("PATH") + 1))
	{
		free_paths(data->paths);
		data->paths = malloc(sizeof(t_path **));
		if (!data->paths)
			return (-1);
		*data->paths = NULL;
		get_paths(data);
	}
	return (0);
}

t_path	*pathnew(char *content)
{
	t_path	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->path = content;
	new->next = NULL;
	return (new);
}

void	pathadd_back(t_path **lst, t_path *new_node)
{
	t_path	*current;

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

void	free_paths(t_path **stack_a)
{
	t_path	*temp;
	t_path	*current;

	current = *stack_a;
	while (current)
	{
		temp = current->next;
		if (current->path)
			free(current->path);
		free(current);
		current = temp;
	}
	free(stack_a);
}
