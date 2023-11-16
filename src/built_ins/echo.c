/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/16 15:42:56 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_echo(t_op **head, int skipped)
{
	if ((*head)->s_char == PIPE)
		return (BREAK);
	if ((*head)->s_char && (*head)->next)
	{
		if ((*head)->next->s_char)
		{
			*head = (*head)->next->next->next;
			skipped = 1;
		}
		if ((*head)->next->next)
		{
			*head = (*head)->next->next;
			skipped = 1;
		}
		else
			return (BREAK);
	}
	if ((*head)->sequence)
		printf("%s", (*head)->sequence);
	if ((*head)->status == UNQUOTED && (*head)->next && (*head)->next->status
		== UNQUOTED)
		printf(" ");
	if (!skipped)
		*head = (*head)->next;
	return (0);
}

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
		if (do_echo(&head, 0) == BREAK)
			break ;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
