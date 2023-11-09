/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:58:25 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The main function initializes a shell data structure, sets up environment variables and paths, and
 * enters a loop until the program is exited.
 * 
 * @param argc The `argc` parameter represents the number of command-line arguments passed to the
 * program. It includes the name of the program itself as the first argument.
 * @param argv An array of strings representing the command-line arguments passed to the program. The
 * first element (argv[0]) is usually the name of the program itself.
 * @param env The `env` parameter is a pointer to an array of strings that represents the environment
 * variables. Each string in the array is in the format "variable=value".
 * 
 * @return The return value of the main function is being set to the value of `data.exit`.
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
	if (loop(&data) == EXIT)
		return (wipe4real(&data), 0);
	if (argc || argv)
		return (data.exit = SUCCESS);
	return (data.exit = SUCCESS);
}
