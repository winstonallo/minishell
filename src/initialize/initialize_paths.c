/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:12:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/22 22:51:42 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "store_paths" adds a new path to a linked list of paths and 
 * returns the exit status of the shell.
 * 
 * @param paths A double pointer to a linked list of paths.
 * @param path A string representing a file path.
 * 
 * @return the value of `data->exit`.
 */
static int	store_paths(t_path **paths, char *path, t_shell *data)
{
	t_path	*new;

	new = pathnew(path);
	if (!new)
		return (-1);
	pathadd_back(paths, new);
	return (data->exit);
}

/**
 * The function `get_paths` retrieves the paths from the `PATH` environment 
 * variable and stores them in a linked list.
 * 
 * @param paths A double pointer to a t_path struct, which is a linked list of
 * paths.
 * @param data The parameter `data` is of type `t_shell*`.
 * 
 * @return an integer value. If the function executes successfully, 
 * it will return 0. If there is an error, it will return -1.
 */
int	get_paths(t_path **paths, t_shell *data)
{
	t_env	*head;
	char	**temp;
	int		i;

	i = -1;
	head = *data->env_list;
	while (head)
	{
		if (!ft_strncmp(head->name, "PATH", 4))
		{
			temp = ft_split(head->line, ':');
			if (!temp)
				return (-1);
			while (temp[++i])
			{
				if (store_paths(paths, temp[i], data) == -1)
					return (free_array(temp), -1);
			}
			free(temp);
		}
		head = head->next;
	}
	return (0);
}
