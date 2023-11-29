/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/29 23:58:42 by sstanfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "echo" prints out the sequences stored in a linked list,
 * with the option to omit a newline character at the end.
 */
int	mooore_ns(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == 'n')
		i++;
	if (i != (int)ft_strlen(str))
		return (1);
	return (0);
}
int	look_for_n(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i][0] != '-' || arg[i][1] != 'n' || mooore_ns(arg[i]) + 1)
		{
			printf("here\n");
			break ;
		}
		else
			i++;
	}
	return (i);
}
int	echo(t_cmd_table *head, int newline, t_shell *data)
{
	int	i;

	i = look_for_n(head->args);
	//printf("i: %d\n", i);
	if (!head->args[1])
		return (SUCCESS);
	if (i == 1)
	{
		while (head->args[i])
		{
			printf("%s", head->args[i]);
			if (head->args[i + 1])
				printf(" ");
			i++;
		}
		newline = 1;
	}
	else
	{
		while (head->args[i])
		{
			printf("%s", head->args[i]);
			if (head->args[i + 1])
				printf(" ");
			i++;
		}
	}
	if (newline)
		printf("\n");
	close(data->stdin_fd);
	wipe4real(data);
	exit(SUCCESS);
}
