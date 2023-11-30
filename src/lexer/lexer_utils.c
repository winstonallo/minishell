/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:13:47 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 12:51:14 by abied-ch         ###   ########.fr       */
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

int	check_schar(t_shell *data)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (data->raw_input[++i])
	{
		if (data->raw_input[i] == '<' || data->raw_input[i] == '>')
			counter++;
		else
			counter = 0;
		if (counter == 3)
		{
			if (data->raw_input[i] == '<')
				print_syntax_error(IN_REDIR);
			else if (data->raw_input[i] == '>')
				print_syntax_error(OUT_REDIR);
			data->exit = 2;
			return (2);
		}
	}
	return (0);
}
