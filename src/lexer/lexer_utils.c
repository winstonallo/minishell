/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:13:47 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/21 23:14:15 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes(t_shell *data)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	while (data->raw_input[++i])
		isquote(data->raw_input[i], &status);
	if (status != UNQUOTED)
	{
		data->exit = 2;
		return (ft_putstr_fd("minishell: unclosed quotes\n", 2), -1);
	}
	return (0);
}
