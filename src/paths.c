/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:12:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/29 22:04:36 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*List utils functions, just need different ones based on list name & content*/
static t_path	*pathnew(char *content)
{
	t_path	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->path = content;
	new->next = NULL;
	return (new);
}

static void	pathadd_back(t_path **lst, t_path *new_node)
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

static int	store_paths(t_path **paths, char *path)
{
	t_path	*new;

	new = pathnew(path);
	if (!new)
		return (free_paths(paths), -1);
	pathadd_back(paths, new);
	return (0);
}

int	get_paths(t_path **paths, char **env)
{
	char	**temp;
	char	**path_array;
	int		i;

	i = -1;
	path_array = env;
	while (*++path_array)
	{
		if (ft_strnstr(*path_array, "PATH", 4))
		{
			temp = ft_split(*path_array + 5, ':');
			if (!temp)
				return (-1);
			while (temp[++i])
			{
				if (store_paths(paths, temp[i]) == -1)
					return (-1);
			}
			free(temp);
		}
	}
	return (0);
}
