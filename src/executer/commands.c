/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/12 17:45:49 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `find_command` checks the first argument of the command table 
 * and executes the corresponding command or returns an error if
 * the command is not found.
 * @return either SUCCESS or FAILURE.
 */
int	myexit(t_shell *data)
{
	int	i;

	i = -1;
	if ((*data->cmd_table)->args[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), FAILURE);
	else if ((*data->cmd_table)->args[1])
	{
		while ((*data->cmd_table)->args[1][++i])
		{
			if (!ft_isdigit((*data->cmd_table)->args[1][i]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd((*data->cmd_table)->args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				data->exit = 2;
				wipe4real(data);
				exit (data->exit);
			}
		}
		data->exit = ft_atoi((*data->cmd_table)->args[1]) % 256;
		wipe4real(data);
		exit (data->exit);
	}
	wipe4real(data);
	exit(SUCCESS);
}

int	find_command(t_shell *data)
{
	if (ft_strncmp((*data->cmd_table)->args[0], "env", 4) == 0)
		return (env(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "exit", 5) == 0)
		return (myexit(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "export", 6) == 0)
		return (export(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "cd", 3) == 0)
		return (cd(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "pwd", 4) == 0)
		return (pwd(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "echo", 5) == 0)
		return (echo(data, 1));
	else if (execute_command(data) == 0)
		return (SUCCESS);
	else
		return (COMMAND_NOT_FOUND);
	return (FAILURE);
}
