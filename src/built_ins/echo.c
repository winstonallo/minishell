/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 13:06:00 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_n(char *arg)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

/**
 * The function "echo" prints out the sequences stored in a linked list,
 * with the option to omit a newline character at the end.
 */
int	echo(t_cmd_table *head, int newline, int i)
{
	if (!head->args[1])
		return (printf("\n"), SUCCESS);
	while (!ft_strncmp(head->args[i], "-n", 2))
	{
		if (check_n(head->args[i]))
		{
			newline = 0;
			i++;
		}
		else
			break ;
	}
	while (head->args[i])
	{
		printf("%s", head->args[i]);
		if (head->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
