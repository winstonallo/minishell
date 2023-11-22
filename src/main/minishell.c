/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/22 23:53:06 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The main function initializes a shell data structure, sets up environment 
 * variables and paths, and enters a loop until the program is exited.
 */
int	main(int argc, char **argv, char **env)
{
	t_shell	data;

	if (initialize_lists(&data) == -1)
		return (1);
	data.environment = env;
	data.exit = 0;
	data.temp = NULL;
	if (get_environment(&data, 0, 0) == -1)
		return (free_env_lists(&data), 1);
	if (get_paths(&data) == -1)
		return (free_env_lists(&data), 1);
	listen();
	if (TEST_MODE)
	{
		if (loop_test(&data, argv[1]) == EXIT)
			return (wipe4real(&data), 0);
	}
	else
		if (loop(&data) == EXIT)
			return (wipe4real(&data), 0);
	if (argc || argv)
		return (data.exit = SUCCESS);
	return (data.exit = SUCCESS);
}
