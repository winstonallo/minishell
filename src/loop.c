/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 12:08:08 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

int	parse_line(t_shell *data)
{
	int	i;

	i = -1;
	if (ft_strncmp(data->raw_input, "env", 4) == 0)
	{
		while (data->environment[++i])
			ft_printf("%s\n", data->environment[i]);
		return (free(data->raw_input), 0);
	}
	else if (ft_strncmp(data->raw_input, "exit", 5) == 0)
		return (free(data->raw_input), EXIT);
	return (COMMAND_NOT_FOUND);
}

void	read_input(t_shell *data)
{
	int	status;

	while (1)
	{
		data->raw_input = readline("$ ");
		if (!data->raw_input)
			return ;
		status = parse_line(data);
		if (status == COMMAND_NOT_FOUND)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(data->raw_input, 2);
			free(data->raw_input);
		}
		else if (status == EXIT)
			exit (EXIT_SUCCESS);
	}
}
