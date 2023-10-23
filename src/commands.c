/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/23 16:34:17 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env(t_shell *data)
{
	int	i;

	i = -1;
	while (data->environment[++i])
		printf("%s\n", data->environment[i]);
}

int	find_command(char *command, t_shell *data)
{
	if (ft_strncmp(command, "env", 4) == 0)
		return (env(data), 0);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (EXIT);
	else
		return (execute_command(data), 0);
	return (COMMAND_NOT_FOUND);
}
