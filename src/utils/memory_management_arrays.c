/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_arrays.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:19:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 11:55:52 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_array(char **arr)
{
	size_t	i;

	i = 0;
	if (arr && *arr)
	{
		while (arr[i])
		{
			freeze(arr[i]);
			i++;
		}
	}
	freeze(arr);
}

void	free_array_arrsize(char **arr, int arr_size)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (i < arr_size)
			free(arr[i++]);
		free(arr);
	}
}
