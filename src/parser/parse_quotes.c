/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:42:54 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/05 16:24:33 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*This is the first step of the parsing process, where we split the input in
tokens based on their quote status.
The outcome of this file is a list of strings with flags for their
quote status (double quoted, single quoted, unquoted)
The quotes are also removed in the process*/
/*Create new sequence of double quoted input, remove the quotes and
set the node's flag accordingly*/
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
		return (data->exit = FAILURE, -1);
	quoteadd_back(data->sequences, new);
	return (data->exit = SUCCESS, i);
}

/*Create new sequence of single quoted input, remove the quotes and
set the node's flag accordingly*/
static int	squotes(char *quoted_sequence, t_shell *data)
{
	size_t		i;
	t_quotes	*new;

	i = 0;
	while (quoted_sequence[i] != '\'')
		i++;
	new = quotenew(quoted_sequence, IN_SINGLE_QUOTES, i);
	if (!new)
		return (data->exit = FAILURE, -1);
	quoteadd_back(data->sequences, new);
	return (data->exit = SUCCESS, i);
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
			return (data->exit = FAILURE, -1);
		quoteadd_back(data->sequences, new);
	}
	return (data->exit = SUCCESS, 0);
}

/*Find out the length of the unquoted sequence (until next quote or
end of line), split it by spaces and create a node for each index of
the array (in 'split_args')
Note that arguments do not have to be space separated, this is the 
first parsing step, there are a lot more to come:)).*/
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
		return (data->exit = SUCCESS, 0);
	temp = ft_strndup(unquoted_sequence, i);
	if (!temp)
		return (data->exit = FAILURE, -1);
	unquoted_array = ft_split(temp, ' ');
	if (!unquoted_array)
		return (data->exit = FAILURE, -1);
	free(temp);
	if (split_args(unquoted_array, data) == -1)
		return (data->exit = FAILURE, -1);
	return (data->exit = SUCCESS, free_array(unquoted_array), i - 1);
}

/*Split user input in sequences based on the quotes.*/
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
			i += squotes(temp + 1, data);
		else
			i += uquote(temp, data);
		if (data->exit == FAILURE)
			return (-1);
	}
	return (data->exit = SUCCESS);
}
