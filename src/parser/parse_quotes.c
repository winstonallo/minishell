/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:42:54 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/18 18:42:25 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `dquotes` adds a new quote sequence to the shell data structure
 *  for a double quoted sequence in a given string.
 * 
 * @param quoted_sequence A pointer to a character array representing a 
 * quoted sequence of characters.
 * @param data The parameter "data" is of type "t_shell", which is a struct 
 * that likely contains
 * information about the shell environment and state. It is being passed as a 
 * pointer to the function.
 * 
 * @return the value of the variable `i`.
 */
static int	dquotes(char *quoted_sequence, t_shell *data)
{
	size_t		i;
	t_quotes	*new;

	i = 0;
	while (quoted_sequence[i] != '\"')
		i++;
	new = quotenew(quoted_sequence, IN_DOUBLE_QUOTES, i);
	if (!new)
		return (-1);
	quoteadd_back(data->sequences, new);
	return (i);
}

/**
 * The function `squotes` adds a new quote sequence to the shell data 
 * structure for a single quote delimited sequence.
 * 
 * @param quoted_sequence A pointer to a character array representing a 
 * quoted sequence of characters.
 * @param data The parameter "data" is of type "t_shell" and is a pointer 
 * to a structure that contains
 * information about the shell.
 * 
 * @return the index of the closing single quote character in the 
 * `quoted_sequence` string.
 */
static int	squotes(char *quoted_sequence, t_shell *data)
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

/**
 * The function "split_args" takes an array of unquoted strings and adds 
 * them to a linked list of quotes in a shell data structure.
 * 
 * @param unquoted_array A pointer to an array of strings (char pointers) 
 * that represent the unquoted arguments.
 * @param data The parameter `data` is of type `t_shell*`.
 * 
 * @return an integer value. If the function executes successfully, 
 * it will return 0. If there is an error, it will return -1.
 */
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
		// if (unquoted_array[i + 1])
		// {
		// 	new = quotenew(" ", UNQUOTED, 1);
		// 	if (!new)
		// 		return (-1);
		// 	quoteadd_back(data->sequences, new);
		// }
	}
	return (0);
}

/**
 * The function `uquote` takes an unquoted sequence of characters, splits it
 * into an array of strings, and then processes each string as separate 
 * arguments.
 * 
 * @param unquoted_sequence A pointer to a character array representing an 
 * unquoted sequence of characters.
 * @param data The parameter `data` is of type `t_shell*`.
 * 
 * @return the value of `i - 1`.
 */
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

/**
 * The function "parse_for_quotes" parses a string for quotes and performs
 *  different actions based on the type of quote encountered.
 * 
 * @param data A pointer to a structure of type t_shell.
 * 
 * @return the value of `data->exit`.
 */
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
	}
	return (data->exit);
}
