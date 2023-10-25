/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:42:54 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/25 22:03:15 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	dquotes(char *quoted_sequence, t_shell *data)
{
	size_t		i;
	t_quotes	*new;

	i = 0;
	while (quoted_sequence[i] != '\"')
	{
		i++;
		if (quoted_sequence[i] == '\\' && quoted_sequence[i + 2])
			i += 2;
	}
	new = quotenew(quoted_sequence, IN_DOUBLE_QUOTES, i);
	if (!new)
		return (-1);
	quoteadd_back(data->sequences, new);
	return (i);
}

static int	squote(char *quoted_sequence, t_shell *data)
{
	size_t		i;
	t_quotes	*new;

	i = 0;
	while (quoted_sequence[i] != '\'')
		i++;
	new = quotenew(quoted_sequence, IN_SINGLE_QUOTES, i);
	if (!new)
		return (-1);
	quoteadd_back(data->sequences, new);
	return (i);
}

static int	split_args(char **unquoted_array, t_shell *data)
{
	int			i;
	int			j;
	t_quotes	*new;

	i = -1;
	while (unquoted_array[++i])
	{
		j = 0;
		while (!myisspace(unquoted_array[i][j]) && unquoted_array[i][j])
			j++;
		new = quotenew(unquoted_array[i], UNQUOTED, j);
		if (!new)
			return (-1);
		quoteadd_back(data->sequences, new);
	}
	return (0);
}

static int	uquote(char *unquoted_sequence, t_shell *data)
{
	size_t		i;
	int			status;
	char		**unquoted_array;
	char		*temp;

	i = 0;
	status = 0;
	while (!isquote(unquoted_sequence[i], &status) && unquoted_sequence[i])
		i++;
	if (i == 0)
		return (0);
	temp = ft_strndup(unquoted_sequence, i);
	if (!temp)
		return (-1);
	unquoted_array = ft_split(temp, ' ');
	if (!unquoted_array)
		return (-1);
	free(temp);
	if (split_args(unquoted_array, data) == -1)
		return (-1);
	return (free_array(unquoted_array), i - 1);
}

int	parse_for_quotes(t_shell *data)
{
	int			quote_status;
	int			i;
	char		*temp;

	i = -1;
	quote_status = 0;
	while (data->raw_input[++i])
	{
		temp = &data->raw_input[i];
		isquote(data->raw_input[i], &quote_status);
		if (quote_status == IN_DOUBLE_QUOTES)
			i += dquotes(temp + 1, data);
		else if (quote_status == IN_SINGLE_QUOTES)
			i += squote(temp + 1, data);
		else
			i += uquote(temp, data);
	}
	return (0);
}
