/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/02 12:23:31 by sstanfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧
Here we look for the commands that we do not execute using execve (the 7
specified in the subject) and execute them if found, otherwise we pass the 
command line to the executing part*/
void	env(t_shell *data)
{
	t_env	*head;

	head = *data->env_list;
	while (head)
	{
		printf("%s=%s\n", head->name, head->line);
		head = head->next;
	}
}

int	find_command(char *command, t_shell *data)
{
	if (ft_strncmp(command, "env", 4) == 0)
		return (env(data), 0);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (EXIT);
	else if (ft_strncmp(command, "export", 6) == 0)
	else if (execute_command(data) == 0)
		return (0);
	return (COMMAND_NOT_FOUND);
}
