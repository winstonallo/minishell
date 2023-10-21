/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/21 18:20:46 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	data;
	t_path	**paths;

	data.environment = env;
	paths = (t_path **)malloc(sizeof(t_path));
	if (!paths)
		return (-1);
	*paths = NULL;
	get_paths(paths, env);
	if (read_input(&data) == EXIT)	
		return (free_paths(paths), free(paths), 0);
	if (argc || argv)
		return (0);
	return (0);
}
