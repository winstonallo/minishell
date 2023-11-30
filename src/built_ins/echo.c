/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 03:53:17 by sstanfel         ###   ########.fr       */
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
int	echo(t_cmd_table *head, int newline)
{
	int	i;

	i = 0;
	if (!head->args[1])
		return (printf("\n"), SUCCESS);
	if (ft_strncmp(head->args[1], "-n", 2) == 0)
	{
		if (check_n(head->args[1]))
		{
			newline = 0;
			i++;
		}
	}
	while (head->args[++i])
	{
		printf("%s", head->args[i]);
		if (head->args[i + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
