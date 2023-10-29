/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:41:10 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/29 22:50:40 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Reinitialize all lists at every new loop only exception is the paths list, 
since we want to keep that during the whole runtime of the program to be able 
to change it durably
NOTE: the paths list only contains the paths, we probably need to make 
one with the whole environment*/
int	initialize_sequences(t_shell *data)
{
	data->sequences = malloc(sizeof(t_quotes **));
	if (!data->sequences)
		return (free(data->paths), -1);
	*data->sequences = NULL;
	data->operators = malloc(sizeof(data->operators));
	if (!data->operators)
		return (-1);
	*data->operators = NULL;
	data->cmd_table = malloc(sizeof(data->cmd_table));
	if (!data->cmd_table)
		return (-1);
	*data->cmd_table = NULL;
	return (0);
}

int	initialize_lists(t_shell *data)
{
	data->paths = (t_path **)malloc(sizeof(t_path));
	if (!data->paths)
		return (-1);
	*data->paths = NULL;
	data->sequences = malloc(sizeof(t_quotes **));
	if (!data->sequences)
		return (free(data->paths), -1);
	*data->sequences = NULL;
	data->operators = malloc(sizeof(data->operators));
	if (!data->operators)
		return (-1);
	*data->operators = NULL;
	data->cmd_table = malloc(sizeof(data->cmd_table));
	if (!data->cmd_table)
		return (-1);
	*data->cmd_table = NULL;
	return (0);
}
