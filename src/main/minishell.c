/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/22 08:49:45 by abied-ch         ###   ########.fr       */
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
		return (data.exit = FAILURE, -1);
	data.environment = env;
	data.exit = 0;
	data.temp = NULL;
	get_environment(&data, 0, 0);
	get_paths(data.paths, &data);
	listen();
	if (TEST_MODE)
		loop_test(&data, argv);
	else
		if (loop(&data) == EXIT)
			return (wipe4real(&data), 0);
	if (argc || argv)
		return (data.exit = SUCCESS);
	return (data.exit = SUCCESS);
}
