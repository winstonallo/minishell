/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_quoted_sequences.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:43:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 17:16:59 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_quoted_sequences(t_quotes **quoted_sequences)
{
	t_quotes	*temp;
	t_quotes	*current;

	current = *quoted_sequences;
	while (current)
	{
		temp = current->next;
		free(current->sequence);
		free(current);
		current = temp;
	}
	free(quoted_sequences);
}
