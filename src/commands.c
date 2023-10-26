/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/26 10:36:50 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧
Here we look for the commands that we do not execute using execve (the 7
specified in the subject) and execute them if found, otherwise we pass the 
command line to the executing part*/
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
	else if (execute_command(data) == 0)
		return (0);
	return (COMMAND_NOT_FOUND);
}
