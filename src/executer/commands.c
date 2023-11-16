/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/16 15:55:44 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `find_command` checks the first argument of the command table 
 * and executes the corresponding command or returns an error if
 * the command is not found.
 * @return either SUCCESS or FAILURE.
 */
int	find_command(t_shell *data)
{
	if (!data->cmd_table || !*data->cmd_table || !(*data->cmd_table)->args
		|| !(*data->cmd_table)->args[0])
		return (0);
	if (ft_strncmp((*data->cmd_table)->args[0], "env", 4) == 0)
		return (env(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "pwd", 4) == 0)
		return (pwd(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "echo", 5) == 0)
		return (echo(data, 1));
	else
		return (COMMAND_NOT_FOUND);
	return (FAILURE);
}
