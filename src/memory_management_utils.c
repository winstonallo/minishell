/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:19:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 14:12:01 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_sequences(t_quotes **sequences)
{
	t_quotes	*current;
	t_quotes	*next;

	current = *sequences;
	while (current)
	{
		next = current->next;
		free(current->sequence);
		free(current);
		current = next;
	}
	free(sequences);
}

void	free_opps(t_op **opps)
{
	t_op	*current;
	t_op	*next;

	current = *opps;
	while (current)
	{
		next = current->next;
		free(current->sequence);
		free(current);
		current = next;
	}
	free(opps);
}

void	free_array(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	free_array_arrsize(char **arr, int arr_size)
{
	int	i;

	i = 0;
	while (i < arr_size)
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
