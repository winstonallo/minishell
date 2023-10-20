/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:42:54 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 16:16:56 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_double_quotes(char *quoted_sequence, t_quotes **quoted_sequences)
{
	size_t		i;
	t_quotes	*new;

	i = 0;
	while (quoted_sequence[i] != '\"')
	{
		i++;
	}	
	new = quotenew(quoted_sequence, IN_DOUBLE_QUOTES, i);
	if (!new)
		return (-1);	
	quoteadd_back(quoted_sequences, new);
	return (i);
}

int	parse_command_line(t_shell *data)
{
	int			indq;
	int 		insq;
	int			i;
	char		*temp;
	t_quotes	**quoted_sequences;

	quoted_sequences = malloc(sizeof(t_quotes **));
	if (!quoted_sequences)
		return (-1);
	*quoted_sequences = NULL;
	i = -1;
	indq = 0;
	insq = 0;
	while (data->raw_input[++i])
	{
		temp = &data->raw_input[i];
		isquote(data->raw_input[i], &insq, &indq);
		if (indq == IN_DOUBLE_QUOTES)
			i += handle_double_quotes(temp + 1, quoted_sequences);
	}
	return (0);
}