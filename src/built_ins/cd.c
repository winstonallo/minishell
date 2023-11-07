/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:29:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/06 08:16:54 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
