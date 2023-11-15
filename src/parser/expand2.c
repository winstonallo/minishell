/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:41:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/15 15:33:47 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stddef.h>

/**
 * The function count_words counts the number of words in a given sequence, 
 * where words are delimitedby '$' characters and whitespace or alphanumeric 
 * characters.
 * 
 * @return the number of words in the given sequence.
 */
size_t	count_words(char *seq)
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
char	**fill_array(size_t *size, char *seq, size_t *pos, t_shell *data)
{
	size_t	i;
	char	**arr;

	i = -1;
	*size = count_words(seq);
	arr = malloc((*size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (++i < *size)
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

static char	*idkyet(char *str, char *temp1, char *temp3, size_t i)
{
	char	*temp2;

	temp2 = NULL;
	temp1 = ft_strndup(str, i);
	if (!temp1)
		return (NULL);
	temp2 = ft_strjoin(temp1, temp3);
	if (!temp2)
		return (free(temp1), NULL);
	free(temp3);
	free(temp1);
	i += 2;
	str = ft_strjoin(temp2, &str[i]);
	if (!str)
		return (free(temp2), NULL);
	i -= 2;
	return (free(temp2), str);
}

/**
 * The function `expand_exitcode` replaces occurrences of "$?" in a string 
 * with the exit code of the shell.
 * 
 * @return a modified version of the input string `str`.
 */
char	*expand_exitcode(char *str, t_shell *data, size_t i)
{
	char	*temp1;
	char	*temp3;

	temp1 = NULL;
	while (str[i])
	{
		if (ft_strnstr(&str[i], "$?", 2))
		{
			temp3 = ft_itoa(data->exit);
			if (!temp3)
				return (NULL);
			str = idkyet(str, temp1, temp3, i);
		}
		i++;
	}
	return (str);
}
