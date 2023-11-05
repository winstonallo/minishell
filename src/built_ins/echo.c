/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/05 17:55:05 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo(t_shell *data)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if ((*data->cmd_table)->args[1]
		&& ft_strncmp((*data->cmd_table)->args[1], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while ((*data->cmd_table)->args[++i])
		printf("%s", (*data->cmd_table)->args[i]);
	if (newline)
		printf("\n");
	return (0);
}
