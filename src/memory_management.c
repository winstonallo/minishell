/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:19:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/21 19:47:50 by abied-ch         ###   ########.fr       */
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

void	free_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_paths(t_path **stack_a)
{
	t_path	*temp;
	t_path	*current;

	current = *stack_a;
	while (current)
	{
		temp = current->next;
		free(current->path);
		free(current);
		current = temp;
	}
	free(stack_a);
}

void	wipe(t_shell *data)
{
	free_paths(data->paths);
	free_sequences(data->sequences);
}
