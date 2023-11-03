/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:22:46 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/03 10:30:44 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export(t_shell *data)
{
	if (ft_strncmp((*data->cmd_table)->args[1], "=", 1) == 0)
		return (-1);
	else if (update_env_list(data) != 0)
		return (-1);
	return (0);
}
