/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:17:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/23 02:08:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_vars(t_shell *data, size_t words)
{
	data->tok.i = -1;
	data->tok.j = 0;
	data->tok.st = 0;
	data->tok.words = words;
	data->tok.tokens = malloc((words + 1) * sizeof(char *));
	if (!data->tok.tokens)
		return (-1);
	return (0);
}
