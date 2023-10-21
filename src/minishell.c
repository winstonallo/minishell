/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/21 19:12:33 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	initialize_lists(t_shell *data)
{
	data->paths = (t_path **)malloc(sizeof(t_path));
	if (!data->paths)
		return (-1);
	*data->paths = NULL;
	data->sequences = malloc(sizeof(t_quotes **));
	if (!data->sequences)
		return (free(data->paths), -1);
	*data->sequences = NULL;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	data;

	if (initialize_lists(&data) == -1)
		return (-1);
	data.environment = env;
	get_paths(data.paths, env);
	if (read_input(&data) == EXIT)	
		return (free_paths(data.paths), free(data.paths), 0);
	if (argc || argv)
		return (0);
	return (0);
}
