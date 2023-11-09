/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:53:13 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `find_command` checks the first argument of the command table and executes the
 * corresponding command or returns an error if the command is not found.
 * 
 * @param data The parameter `data` is of type `t_shell*`, which is a pointer to a structure `t_shell`.
 * 
 * @return The function `find_command` returns an integer value. The possible return values are:
 */
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
