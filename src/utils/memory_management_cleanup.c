/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_cleanup.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:17 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 10:56:45 by abied-ch         ###   ########.fr       */
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
	freeze(data->cwd);
	if (data->stdin_fd != NO_FD)
		close(data->stdin_fd);
	free_dox(data->dox);
	if (data->sorted_env)
		free_environment(data->sorted_env);
	wipe(data);
}

int	wipe(t_shell *data)
{
	freeze(data->raw_input);
	free_array(data->environment);
	if (data->operators)
		free_opps(data->operators);
	if (data->sequences)
		free_sequences(data->sequences);
	if (data->cmd_table)
		free_cmd_tables(data->cmd_table);
	return (1);
}
