/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 14:07:31 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "echo" prints out the sequences stored in a linked list,
 * with the option to omit a newline character at the end.
 */
int	echo(t_shell *data)
{
	int			newline;
	t_op		*head;

	newline = 1;
	head = (*data->operators)->next;
	if (head->sequence
		&& ft_strncmp(head->sequence, "-n", 3) == 0)
	{
		newline = 0;
		head = head->next;
		head = head->next;
	}
	while (head)
	{
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
