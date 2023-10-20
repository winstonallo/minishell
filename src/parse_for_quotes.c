/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:42:54 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 21:28:54 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_double_quotes(char *quoted_sequence, t_shell *data)
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
	printf("double quoted sequence: %s\n", new->sequence);
	quoteadd_back(data->sequences, new);
	return (i);
}

static int	handle_single_quotes(char *quoted_sequence, t_shell *data)
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
	printf("single quoted sequence: %s\n", new->sequence);
	quoteadd_back(data->sequences, new);
	return (i);
}

static int	handle_unquoted(char *unquoted_sequence, t_shell *data)
{
	size_t		i;
	t_quotes	*new;
	int			status;

	i = 0;
	status = 0;
	while (!isquote(unquoted_sequence[i], &status) && unquoted_sequence[i])
		i++;
	if (i == 0)
		return (0);
	new = quotenew(unquoted_sequence, UNQUOTED, i);
	if (!new)
		return (-1);
	printf("unquoted sequence: %s\n", new->sequence);
	quoteadd_back(data->sequences,  new);
	return (i);
}

int	parse_for_quotes(t_shell *data)
{
	int			quote_status;
	int			i;
	char		*temp;

	data->sequences = malloc(sizeof(t_quotes **));
	if (!data->sequences)
		return (-1);
	*data->sequences = NULL;
	i = -1;
	quote_status = 0;
	while (data->raw_input[++i])
	{
		temp = &data->raw_input[i];
		isquote(data->raw_input[i], &quote_status);
		if (quote_status == IN_DOUBLE_QUOTES)
			i += handle_double_quotes(temp + 1, data);
		else if (quote_status == IN_SINGLE_QUOTES)
			i += handle_single_quotes(temp + 1, data);
		else
			i += handle_unquoted(temp, data);
	}
	free_quoted_sequences(data->sequences);
	return (0);
}
