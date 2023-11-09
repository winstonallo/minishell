/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:29:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:46:11 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `cd` changes the current directory in a shell program and updates the prompt.
 * 
 * @param data A pointer to a structure of type t_shell, which contains information about the shell
 * environment and command table (args[1] being the cd parameter).
 * 
 * @return either SUCCESS or FAILURE.
 */
int	cd(t_shell *data)
{
	if (chdir((*data->cmd_table)->args[1]) == -1)
	{
		perror("minishell: cd");
		return (FAILURE);
	}
	if (get_prompt(data, 0) == -1)
		return (FAILURE);
	return (SUCCESS);
}
