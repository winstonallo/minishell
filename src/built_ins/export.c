/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:45:47 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 17:33:25 by sstanfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_env_alpha(t_shell *data)
{
	//env nicht nach alphabehet sortiert == BAUSTELLE
	env(data);
	return (0);
}

int	export(t_shell *data)
{
	int		i;
	char	**arg;

	i = 1;
	arg = (*data->cmd_table)->args;
	if (arg[i] == NULL)
		print_env_alpha(data);
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
