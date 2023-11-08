/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:11:39 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 22:12:12 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_env_sorted(t_shell *data)
{
	//env nicht nach alphabehet sortiert == BAUSTELLE
	env(data);
	return (0);
}

int	expoort(t_shell *data)
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
