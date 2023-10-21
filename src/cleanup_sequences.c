/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_sequences.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:43:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 18:34:02 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_sequences(t_quotes **sequences)
{
	t_quotes	*temp;
	t_quotes	*current;

	current = *sequences;
	while (current)
	{
		temp = current->next;
		free(current->sequence);
		free(current);
		current = temp;
	}
	free(sequences);
}

char	**free_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}