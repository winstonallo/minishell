/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:45:47 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/06 08:45:51 by abied-ch         ###   ########.fr       */
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
		return (data->exit);
	else if (update_env_list(data) != 0)
		return (FAILURE);
	return (SUCCESS);
}
