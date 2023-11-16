/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/16 14:56:13 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "echo" prints out the sequences stored in a linked list,
 * with the option to omit a newline character at the end.
 */
int	echo(t_shell *data, int newline)
{
	t_op		*head;

	if ((*data->operators)->next)
		head = (*data->operators)->next;
	else
		return (printf("\n"), SUCCESS);
	if (head->sequence
		&& ft_strncmp(head->sequence, "-n", 3) == 0)
	{
		newline = 0;
		head = head->next;
	}
	while (head)
	{
		if (head->s_char == PIPE)
			break ;
		if (head->s_char && head->next)
		{
			if (head->next->next)
				head = head->next->next;
			else
			 	break ;
		}	
		if (head->sequence)
			printf("%s", head->sequence);
		if (head->status == UNQUOTED && head->next && head->next->status
			== UNQUOTED)
			printf(" ");
		head = head->next;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
