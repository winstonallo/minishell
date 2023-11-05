/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:41:10 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/05 17:47:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Reinitialize all lists at every new loop only exception is the paths list, 
since we want to keep that during the whole runtime of the program to be able 
to change it durably
NOTE: the paths list only contains the paths, we probably need to make 
one with the whole environment*/
int	initialize_sequences(t_shell *data)
{
	data->sequences = malloc(sizeof(t_quotes **));
	if (!data->sequences)
		return (wipe4real(data), data->exit = FAILURE);
	*data->sequences = NULL;
	data->operators = malloc(sizeof(data->operators));
	if (!data->operators)
		return (wipe4real(data), data->exit = FAILURE);
	*data->operators = NULL;
	data->cmd_table = malloc(sizeof(data->cmd_table));
	if (!data->cmd_table)
		return (wipe4real(data), data->exit = FAILURE);
	*data->cmd_table = NULL;
	data->temp = NULL;
	return (data->exit);
}

int	initialize_lists(t_shell *data)
{
	data->env_list = malloc(sizeof(data->env_list));
	if (!data->env_list)
		return (data->exit = FAILURE);
	*data->env_list = NULL;
	data->paths = malloc(sizeof(data->paths));
	if (!data->paths)
		return (free(data->env_list), data->exit = FAILURE);
	*data->paths = NULL;
	data->sequences = malloc(sizeof(data->sequences));
	if (!data->sequences)
		return (free(data->paths), data->exit = FAILURE);
	*data->sequences = NULL;
	data->operators = malloc(sizeof(data->operators));
	if (!data->operators)
		return (free(data->env_list), free(data->paths),
			data->exit = FAILURE);
	*data->operators = NULL;
	data->cmd_table = malloc(sizeof(data->cmd_table));
	if (!data->cmd_table)
		return (free(data->env_list), free(data->paths),
			free(data->operators), data->exit = FAILURE);
	*data->cmd_table = NULL;
	data->temp = NULL;
	data->prompt = NULL;
	return (data->exit);
}
