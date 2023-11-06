/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/06 08:23:28 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*This is only a wrapper function, loop.c is where the real shit happens
Here we initialize the lists for the first time, get the environment and
the paths (all of the one-time things)*/
int	main(int argc, char **argv, char **env)
{
	t_shell	data;

	if (initialize_lists(&data) == -1)
		return (data.exit = FAILURE, -1);
	data.environment = env;
	data.exit = 0;
	data.temp = NULL;
	get_environment(&data, 0, 0);
	get_paths(data.paths, &data);
	if (loop(&data) == EXIT)
		return (wipe4real(&data), 0);
	if (argc || argv)
		return (data.exit = SUCCESS);
	return (data.exit = SUCCESS);
}
