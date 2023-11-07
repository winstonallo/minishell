/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/06 10:52:44 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo(t_shell *data)
{
	int			newline;
	t_quotes	*head;

	newline = 1;
	head = (*data->sequences)->next;
	if (head->sequence
		&& ft_strncmp(head->sequence, "-n", 3) == 0)
	{
		newline = 0;
		head = head->next;
	}
	while (head)
	{
		if (head->sequence)
			printf("%s", head->sequence);
		if (head->next && head->next->status == UNQUOTED && head->sequence)
			printf(" ");
		head = head->next;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
