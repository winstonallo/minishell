/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:22:46 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/05 17:44:43 by sstanfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	export(t_shell *data)
{
	if((*data->cmd_table)->args[1] == NULL)
	{
		env(data);
		return (0);
	}
	if (ft_strncmp((*data->cmd_table)->args[1], "=", 1) == 0)
		return (-1);
	else if (update_env_list(data) != 0)
		return (-1);
	return (0);
}
