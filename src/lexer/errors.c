/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:43:39 by arthur            #+#    #+#             */
/*   Updated: 2023/11/09 22:05:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_quotes(t_shell *data)
{
	int	i;
	int	status;

	i = -1;
	while (data->raw_input[++i])
		isquote(data->raw_input[i], &status);
	if (status != UNQUOTED)
		return (-1);
	return (0);
}

int	lexer(t_shell *data)
{
	if (check_quotes(data) == -1)
		return (ft_putstr_fd("minishell: unclosed quotes\n", 2), -1);
	return (0);
}
