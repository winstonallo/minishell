/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:52:25 by arthur            #+#    #+#             */
/*   Updated: 2023/11/09 14:08:03 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//env nicht nach alphabehet sortiert == BAUSTELLE
static int	print_env_sorted(t_shell *data)
{
	env(data);
	return (0);
}

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

	i = 1;
	arg = (*data->cmd_table)->args;
	if (arg[i] == NULL)
		print_env_sorted(data);
	while (arg[i])
	{
		if (export_error(arg[i]) == 1)
			return (FAILURE);
		else if (export_error(arg[i]) == 2)
			return (SUCCESS);
		else if (update_env_list(data) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
