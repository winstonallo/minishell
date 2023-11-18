/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:52:25 by arthur            #+#    #+#             */
/*   Updated: 2023/11/18 15:41:08 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//env nicht nach alphabehet sortiert == BAUSTELLE
// static int	print_env_sorted(t_shell *data)
// {
// 	env(data);
// 	return (0);
// }
/**
 * The function "export" is used to update the environment list with the 
 * given arguments and returns a success or failure status.
 * 
 * @return either SUCCESS or FAILURE.
 */
int	export(t_shell *data)
{
	int		i;
	char	**arg;
	int		argname;

	i = 1;
	arg = (*data->cmd_table)->args;
	argname = 1;
	while (arg[i])
	{
		if (export_error(arg[i], argname) == 1)
			return (data->exit = FAILURE);
		else if (export_error(arg[i], argname) == 2)
			return (data->exit = SUCCESS);
		else if (update_env_list(data) != 0)
			return (data->exit = FAILURE);
		argname = 0;
		i++;
	}
	return (SUCCESS);
}
