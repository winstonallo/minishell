/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:16:38 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/21 19:16:44 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_quote_list(t_quotes **sequences)
{
	t_quotes	*head;

	head = *sequences;
	while (head != NULL)
	{
		if (head->status == IN_DOUBLE_QUOTES)
			printf("Double Quoted Sequence: %s\n", head->sequence);
		else if (head->status == IN_SINGLE_QUOTES)
			printf("Single Quoted Sequence: %s\n", head->sequence);
		else if (head->status == UNQUOTED)
			printf("Unquoted Sequence: %s\n", head->sequence);
		head = head->next;
	}
}
