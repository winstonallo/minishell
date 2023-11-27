/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/27 15:03:10 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	checkcmd(t_shell *data)
{
	if (!data->cmd_table || !*data->cmd_table || !(*data->cmd_table)->args
		|| !(*data->cmd_table)->args[0])
		return (SUCCESS);
	if (ft_strncmp((*data->cmd_table)->args[0], "exit", 5) == 0)
		return (myexit(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "export", 6) == 0)
		return (export(data));
	else if (!ft_strncmp((*data->cmd_table)->args[0], "unset", 6))
		return (unset(data), 0);
	else if (!ft_strncmp((*data->cmd_table)->args[0], "cd", 3))
		return (cd(data, 0), update_pwd(data));
	return (data->exit = COMMAND_NOT_FOUND);
}

/**
 * The function `find_command` checks the first argument of the command table 
 * and executes the corresponding command or returns an error if
 * the command is not found.
 * @return either SUCCESS or FAILURE.
 */
int	find_command(t_shell *data, t_cmd_table *head)
{
	if (!head || !head->args || !head->args[0])
		return (0);
	if (!ft_strncmp(head->args[0], "env", 4))
		return (env(data));
	else if (!ft_strncmp(head->args[0], "pwd", 4))
		return (pwd(data));
	else if (!ft_strncmp(head->args[0], "echo", 5))
		return (echo(head, 1));
	else
		return (data->exit = COMMAND_NOT_FOUND);
	return (FAILURE);
}
