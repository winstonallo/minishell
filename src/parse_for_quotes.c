/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:42:54 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 18:13:23 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_double_quotes(char *quoted_sequence, t_quotes **quoted_sequences)
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
	ft_printf("double quoted sequence: %s\n", new->sequence);
	quoteadd_back(quoted_sequences, new);
	return (i);
}

static int	handle_single_quotes(char *quoted_sequence, t_quotes **quoted_sequences)
{
	size_t		i;
	t_quotes	*new;

	i = 0;
	while (quoted_sequence[i] != '\'')
	{
		i++;
	}
	new = quotenew(quoted_sequence, IN_SINGLE_QUOTES, i);
	if (!new)
		return (-1);
	ft_printf("single quoted sequence: %s\n", new->sequence);
	quoteadd_back(quoted_sequences, new);
	return (i);
}

int	parse_for_quotes(t_shell *data)
{
	int			indq;
	int			insq;
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
		else if (insq == IN_SINGLE_QUOTES)
			i += handle_single_quotes(temp + 1, quoted_sequences);
	}
	free_quoted_sequences(quoted_sequences);
	return (0);
}
