/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:41:10 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:56:43 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function initializes sequences, operators, cmd_table, temp, and s_char_tmp variables in the
 * t_shell struct and returns the exit status.
 * 
 * @param data The parameter `data` is of type `t_shell*`, which is a pointer to a structure of type
 * `t_shell`.
 * 
 * @return the value of `data->exit`.
 */
int	initialize_sequences(t_shell *data)
{
	data->sequences = malloc(sizeof(t_quotes **));
	if (!data->sequences)
		return (wipe4real(data), -1);
	*data->sequences = NULL;
	data->operators = malloc(sizeof(data->operators));
	if (!data->operators)
		return (wipe4real(data), -1);
	*data->operators = NULL;
	data->cmd_table = malloc(sizeof(data->cmd_table));
	if (!data->cmd_table)
		return (wipe4real(data), -1);
	*data->cmd_table = NULL;
	data->temp = NULL;
	data->s_char_tmp = 0;
	return (data->exit);
}

/**
 * The function initializes lists and variables in a shell data structure.
 * 
 * @param data The parameter `data` is of type `t_shell*`, which is a pointer to a structure of type
 * `t_shell`.
 * 
 * @return an integer value. If the function is successful, it will return 0. If there is an error, it
 * will return -1.
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
	if (initialize_sequences(data) == -1)
		return (-1);
	data->temp = NULL;
	data->prompt = NULL;
	return (0);
}
