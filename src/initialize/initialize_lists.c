/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:41:10 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/23 03:14:17 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function initializes sequences, operators, cmd_table, temp, and 
 * s_char_tmp variables in the t_shell struct and returns the exit status.
 */
int	initialize_sequences(t_shell *data)
{
	data->temp = NULL;
	data->validexit = 1;
	data->allocated = 0;
	data->s_char_tmp = 0;
	data->cmd_table = NULL;
	data->sequences = malloc(sizeof(t_quotes **));
	if (!data->sequences)
		return (-1);
	*data->sequences = NULL;
	data->operators = malloc(sizeof(data->operators));
	if (!data->operators)
		return (freeze(data->sequences), -1);
	*data->operators = NULL;
	data->cmd_table = malloc(sizeof(data->cmd_table));
	if (!data->cmd_table)
		return (freeze(data->sequences), freeze(data->operators), -1);
	*data->cmd_table = NULL;
	return (data->exit);
}

/**
 * The function initializes lists and variables in the shell data structure.
 *
 */
int	initialize_lists(t_shell *data)
{
	data->env_list = malloc(sizeof(data->env_list));
	if (!data->env_list)
		return (-1);
	*data->env_list = NULL;
	data->paths = malloc(sizeof(data->paths));
	if (!data->paths)
		return (free(data->env_list), -1);
	*data->paths = NULL;
	data->temp = NULL;
	data->prompt = NULL;
	data->exit = 0;
	return (0);
}
