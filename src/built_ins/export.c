/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:22:46 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/05 16:16:14 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export(t_shell *data)
{
	if (ft_strncmp((*data->cmd_table)->args[1], "=", 1) == 0)
		return (data->exit = FAILURE);
	else if (update_env_list(data) != 0)
		return (data->exit = FAILURE, -1);
	return (data->exit = SUCCESS);
}
