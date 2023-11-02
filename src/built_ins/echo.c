/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/02 16:52:37 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo(t_shell *data, int newline)
{
	int	i;

	i = 0;
	if (ft_strncmp((*data->cmd_table)->args[1], "-n", 3) == 0)
		newline = 1;
	while ((*data->cmd_table)->args[++i])
		printf("%s", (*data->cmd_table)->args[i]);
}
