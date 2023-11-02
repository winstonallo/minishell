/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/02 13:09:01 by sstanfel         ###   ########.fr       */
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

int	find_command(t_shell *data)
{
	if (ft_strncmp((*data->cmd_table)->args[0], "env", 4) == 0)
		return (env(data), 0);
	else if (ft_strncmp((*data->cmd_table)->args[0], "exit", 5) == 0)
		return (EXIT);
	else if (ft_strncmp((*data->cmd_table)->args[0], "export", 6) == 0)
		return (export(data), 0);
	else if (ft_strncmp((*data->cmd_table)->args[0], "cd", 3) == 0)
		return (cd(data));	
	else if (execute_command(data) == 0)
		return (0);
	return (COMMAND_NOT_FOUND);
}
