/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/19 19:28:31 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	get_paths(t_shell *data, t_path **paths)
{
	char	**temp;
	char	**path_array;
	t_path	*new;
	int		i;

	i = -1;
	path_array = data->environment;
	while (*path_array)
	{
		if (ft_strnstr(*path_array, "PATH", 4))
		{
			*path_array += 5;
			temp = ft_split(*path_array, ':');
			if (!temp)
				return (-1);
			while (temp[++i])
			{
				new = pathnew(temp[i]);
				if (!new)
					return (free_paths(paths), -1);
				pathadd_back(paths, new);
			}
			free(temp);
		}
		path_array++;
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_shell	data;
	t_path	**paths;
	
	data.environment = env;
	paths = (t_path **)malloc(sizeof(t_path));
	if (!paths)
		return (-1);
	get_paths(&data, paths);
	read_input(&data);
	if (argc || argv)
		return (0);
	return (0);
}