/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:29:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/12 17:27:54 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `cd` changes the current directory in a shell program and 
 * updates the prompt.
 * @return either SUCCESS or FAILURE.
 */
int	cd(t_shell *data)
{
	if ((*data->cmd_table)->args[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), FAILURE);
	if (chdir((*data->cmd_table)->args[1]) == -1)
	{
		perror("minishell: cd");
		return (FAILURE);
	}
	if (get_prompt(data, 0) == -1)
		return (FAILURE);
	return (SUCCESS);
}
