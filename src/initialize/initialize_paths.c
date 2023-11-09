/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:12:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:57:07 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "store_paths" adds a new path to a linked list of paths and returns the exit status of
 * the shell.
 * 
 * @param paths A double pointer to a linked list of t_path structures.
 * @param path A string representing a file path.
 * @param data The "data" parameter is of type "t_shell" and is a pointer to a structure that contains
 * information about the shell. It likely includes variables and settings related to the shell's
 * behavior and configuration.
 * 
 * @return the value of `data->exit`.
 */
static int	store_paths(t_path **paths, char *path, t_shell *data)
{
	t_path	*new;

	new = pathnew(path);
	if (!new)
		return (free_paths(paths), -1);
	pathadd_back(paths, new);
	return (data->exit);
}

/**
 * The function `get_paths` retrieves the paths from the `PATH` environment variable and stores them in
 * a linked list.
 * 
 * @param paths A double pointer to a t_path struct, which is a linked list of paths.
 * @param data The parameter `data` is of type `t_shell*`.
 * 
 * @return an integer value. If the function executes successfully, it will return 0. If there is an
 * error, it will return -1.
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
					return (-1);
			}
			free(temp);
		}
		head = head->next;
	}
	return (0);
}
