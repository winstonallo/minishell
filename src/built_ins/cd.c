/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:29:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/20 18:12:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `cd` changes the current directory in a shell program and 
 * updates the prompt.
 * @return either SUCCESS or FAILURE.
 */
int	cd(t_shell *data, int i)
{
	while ((*data->cmd_table)->args[i])
		i++;
	if (i > 2)
	{
		data->exit = FAILURE;
		return (ft_putstr_fd("cd: too many arguments\n", 2), FAILURE);
	}
	else if (i == 1)
		return (ft_putstr_fd("cd: argument needed\n", 2), FAILURE);
	if (chdir((*data->cmd_table)->args[1]) == -1)
	{
		perror("minishell: cd");
		data->exit = FAILURE;
		return (FAILURE);
	}
	if (get_prompt(data, 0) == -1)
		return (FAILURE);
	return (SUCCESS);
}
