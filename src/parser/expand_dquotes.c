/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:41:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/13 18:43:09 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function count_words counts the number of words in a given sequence, 
 * where words are delimitedby '$' characters and whitespace or alphanumeric 
 * characters.
 * 
 * @return the number of words in the given sequence.
 */
static size_t	count_words(char *seq)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (seq[i])
	{
		if (seq[i] == '$' && myisspace(seq[i + 1]))
			i += 2;
		else if (seq[i] == '$')
		{
			ret++;
			i++;
			while (seq[i] && seq[i] != '$' && !myisspacealnum(seq[i]))
				i++;
		}
		else
		{
			ret++;
			while (seq[i] && seq[i] != '$')
				i++;
		}
	}
	return (ret);
}

/**
 * The function `get_next_word` extracts the next word from 
 * a given sequence of characters, considering
 * special cases for arguments starting with a '$' symbol.
 * 
 * @param seq A pointer to a character array (string) that represents a 
 * sequence of characters.
 * @param pos The `pos` parameter is a pointer to a `size_t` variable. 
 * It is used to keep track of the current position in the sequence `seq`. 
 * The function updates the value of `pos` to the new position
 * after extracting the next word.
 */
static char	*get_next_word(char *seq, size_t *pos)
{
	size_t	i;
	int		in_arg;
	char	*ret;

	i = *pos;
	in_arg = 0;
	if (seq[i] && seq[i + 1] && seq[i++] == '$' && (ft_isalnum(seq[i + 1])))
		in_arg = 1;
	while (seq[i])
	{
		if (seq[i] == '$' && !ft_isalnum(seq[i + 1]))
			i++;
		if (((myisspace(seq[i]) && in_arg) || (seq[i] == '$') || (!seq[i + 1])))
		{
			if (!seq[i + 1])
				i++;
			ret = ft_strndup(&seq[*pos], i - *pos);
			if (!ret)
				return (NULL);
			*pos = i;
			return (ret);
		}
		i++;
	}
	return (ft_strdup(""));
}

/**
 * The function `fill_array` takes in an array size, a sequence of 
 * characters, a position, and a shell data structure, and returns an array
 * of strings where each string is a word from the sequence, with
 * any variables replaced by their corresponding values from the shell
 * data structure.
 */
char	**fill_array(size_t arr_size, char *seq, size_t *pos, t_shell *data)
{
	size_t	i;
	char	**arr;

	i = -1;
	arr = malloc((arr_size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (++i < arr_size)
	{
		arr[i] = get_next_word(seq, pos);
		if (!arr[i])
			return (free(arr), NULL);
		if (arr[i][0] == '$' && (isalnum(arr[i][1])))
			arr[i] = replace(arr[i], data);
	}
	arr[i] = NULL;
	return (arr);
}

/**
 * The function `expand_exitcode` replaces occurrences of "$?" in a string 
 * with the exit code of the shell.
 * 
 * @return a modified version of the input string `str`.
 */
static char	*expand_exitcode(char *str, t_shell *data)
{
	size_t	i;
	char	*temp;
	char	*temptemp;
	char	*temptemptemp;

	i = 0;
	temp = NULL;
	temptemp = NULL;
	while (str[i])
	{
		if (ft_strnstr(&str[i], "$?", 2))
		{
			temp = ft_strndup(str, i);
			if (!temp)
				return (NULL);
			temptemptemp = ft_itoa(data->exit);
			if (!temptemptemp)
				return (NULL);
			temptemp = ft_strjoin(temp, temptemptemp);
			if (!temptemp)
				return (free(temp), NULL);
			free(temptemptemp);
			free(temp);
			i += 2;
			str = ft_strjoin(temptemp, &str[i]);
			if (!str)
				return (free(temptemp), NULL);
			i -= 2;
		}
		i++;
	}
	return (free(temptemp), str);
}

/**
 * The function "expand_dquotes" expands double quotes in a given sequence 
 * by replacing variables and command substitutions.
 * 
 * @param node A pointer to a node of the list of quote-type separated 
 * sequences.
 */
int	expand_dquotes(t_quotes *node, t_shell *data, size_t i, size_t pos)
{
	size_t	size;
	char	**arr;

	size = count_words(node->sequence);
	arr = fill_array(size, node->sequence, &pos, data);
	if (!arr)
		return (-1);
	while (++i < size)
	{
		if (!data->temp)
			data->temp = ft_strndup(arr[i], ft_strlen(arr[i]));
		else
			data->temp = ft_strjoin(node->sequence, arr[i]);
		if (!data->temp)
		{
			free_array(arr);
			return (-1);
		}
		free(node->sequence);
		data->temp = expand_exitcode(data->temp, data);
		node->sequence = data->temp;
	}
	data->temp = NULL;
	return (free_array_arrsize(arr, size), 0);
}
