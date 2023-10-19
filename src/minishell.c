/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/19 19:20:54 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	get_paths(t_shell *data, t_path **paths)
{
	char	**temp;
	t_path	*new;
	int		i;

	i = -1;
	while (*data->environment)
	{
		if (ft_strnstr(*data->environment, "PATH", 4))
		{
			*data->environment += 5;
			temp = ft_split(*data->environment, ':');
			if (!temp)
				return (-1);
			while (temp[++i])
			{
				new = pathnew(temp[i]);
				if (!new)
					return (free_paths(paths), -1);
				pathadd_back(paths, new);
				ft_printf("%s\n", new->path);
			}
			free(temp);
		}
		data->environment++;
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