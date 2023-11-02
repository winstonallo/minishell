/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:22:46 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/02 13:03:14 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(t_shell *data)
{
	if (chdir((*data->cmd_table)->args[1]) == -1)
	{
		perror("minishell: cd");
		return (-1);
	}
	return (0);
}
