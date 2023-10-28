/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/26 10:03:44 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	data;

	if (initialize_lists(&data) == -1)
		return (-1);
	data.environment = env;
	get_paths(data.paths, env);
	if (loop(&data) == EXIT)
		return (free_paths(data.paths), wipe(&data), 0);
	if (argc || argv)
		return (0);
	return (0);
}
