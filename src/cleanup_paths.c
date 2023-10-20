/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:14:42 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 16:34:38 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_paths(t_path **stack_a)
{
	t_path	*temp;
	t_path	*current;

	current = *stack_a;
	while (current)
	{
		temp = current->next;
		free(current);
		free(current->path);
		current = temp;
	}
	return (0);
}
