/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:41:10 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/23 16:45:17 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	initialize_sequences(t_shell *data)
{
	data->sequences = malloc(sizeof(t_quotes **));
	if (!data->sequences)
		return (free(data->paths), -1);
	*data->sequences = NULL;
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
	return (0);
}
