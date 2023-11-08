/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 21:53:36 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (head->status == UNQUOTED && head->next && head->next->status == UNQUOTED)
			printf(" ");
		head = head->next;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
	return (SUCCESS);
}
// int	echo(t_shell *data)
// {
// 	int			newline;
// 	int			i;
// 	t_cmd_table	*head;

// 	i = 0;
// 	newline = 1;
// 	head = (*data->cmd_table);
// 	if (head->args
// 		&& ft_strncmp(head->args[1], "-n", 3) == 0)
// 	{
// 		i++;
// 		newline = 0;
// 		head = head->next;
// 	}
// 	while (head->args[++i])
// 	{
// 		if (head->args[i])
// 			printf("%s", head->args[i]);
// 	}
// 	if (newline)
// 		printf("\n");
// 	return (SUCCESS);
// }
