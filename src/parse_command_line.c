/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:42:54 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 13:23:15 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_command_line(t_shell *data)
{
	int	indq;
	int insq;
	int	i;
	
	i = -1;
	indq = 0;
	insq = 0;
	while (data->raw_input[++i])
	{
		isquote(data->raw_input[i], &insq, &indq);
		if (indq == IN_DOUBLE_QUOTES)
			printf("currently in double quotes, ignoring special characters\n");
	}
}