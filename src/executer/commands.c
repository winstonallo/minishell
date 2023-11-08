/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 22:17:17 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧
Here we look for the commands that we do not execute using execve (the 7
specified in the subject) and execute them if found, otherwise we pass the 
command line to the executing part*/
static int	print_env_sorted(t_shell *data)
{
	//env nicht nach alphabehet sortiert == BAUSTELLE
	env(data);
	return (0);
}

static int	export(t_shell *data)
{
	int		i;
	char	**arg;

	i = 1;
	arg = (*data->cmd_table)->args;
	if (arg[i] == NULL)
		print_env_sorted(data);
	while (arg[i])
	{
		if (export_error(arg[i]) == 1)
			return (FAILURE);
		else if (export_error(arg[i]) == 2)
			return (SUCCESS);
		else if (update_env_list(data) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	find_command(t_shell *data)
{
	if (ft_strncmp((*data->cmd_table)->args[0], "env", 4) == 0)
		return (env(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "exit", 5) == 0)
		return (printf("exit\n"), EXIT);
	else if (ft_strncmp((*data->cmd_table)->args[0], "export", 6) == 0)
		return (export(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "cd", 3) == 0)
		return (cd(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "pwd", 4) == 0)
		return (pwd(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "echo", 5) == 0)
		return (echo(data));
	else if (execute_command(data) == 0)
		return (SUCCESS);
	else
		return (COMMAND_NOT_FOUND);
	return (FAILURE);
}
