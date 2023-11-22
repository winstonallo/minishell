/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_cleanup.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:17 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/22 22:28:13 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_lists(t_shell *data)
{
	free_environment(data->env_list);
	free_paths(data->paths);
}

void	wipe4real(t_shell *data)
{
	free_paths(data->paths);
	free_environment(data->env_list);
	freeze(data->prompt);
	wipe(data);
}

void	wipe(t_shell *data)
{
	freeze(data->raw_input);
	if (data->operators)
		free_opps(data->operators);
	if (data->sequences)
		free_sequences(data->sequences);
	if (data->cmd_table)
		free_cmd_tables(data->cmd_table);
}
