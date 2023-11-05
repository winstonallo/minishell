/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:12:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/05 16:22:49 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	store_paths(t_path **paths, char *path, t_shell *data)
{
	t_path	*new;

	new = pathnew(path);
	if (!new)
		return (data->exit = FAILURE, free_paths(paths), -1);
	pathadd_back(paths, new);
	return (data->exit = SUCCESS, 0);
}

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
				return (data->exit = FAILURE, -1);
			while (temp[++i])
			{
				if (store_paths(paths, temp[i], data) == -1)
					return (data->exit = FAILURE);
			}
			free(temp);
		}
		head = head->next;
	}
	return (data->exit = SUCCESS);
}
