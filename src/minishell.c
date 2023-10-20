/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 16:36:48 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **env)
{
	t_shell	data;
	t_path	**paths;

	data.environment = env;
	paths = (t_path **)malloc(sizeof(t_path));
	if (!paths)
		return (-1);
	*paths = NULL;
	get_paths(&data, paths);
	if (read_input(&data) == EXIT)
		return (free(paths), free_paths(paths));
	if (argc || argv)
		return (0);
	return (0);
}
