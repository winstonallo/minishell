/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/26 23:04:24 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	do_echo(t_cmd_table **head, int skipped)
// {
// 	if ((*head)->s_char == PIPE)
// 		return (BREAK);
// 	if ((*head)->s_char && (*head)->next)
// 	{
// 		if ((*head)->next->s_char)
// 		{
// 			*head = (*head)->next->next->next;
// 			skipped = 1;
// 		}
// 		if ((*head)->next->next)
// 			*head = (*head)->next->next;
// 		else if (!(*head)->next)
// 			return (BREAK);
// 	}
// 	if ((*head)->sequence)
// 		printf("%s", (*head)->sequence);
// 	if ((*head)->status == UNQUOTED && (*head)->next && (*head)->next->status
// 		== UNQUOTED)
// 		printf(" ");
// 	if (!skipped)
// 		*head = (*head)->next;
// 	return (0);
// }

/**
 * The function "echo" prints out the sequences stored in a linked list,
 * with the option to omit a newline character at the end.
 */
int	echo(t_cmd_table *head, int newline)
{
	int	i;

	i = 0;
	if (!head->args[1])
		return (printf("\n"), SUCCESS);
	if (ft_strncmp(head->args[1], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (head->args[++i])
	{
		printf("%s", head->args[i]);
		if (head->args[i + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");
	exit(SUCCESS);
}
