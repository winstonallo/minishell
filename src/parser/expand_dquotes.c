/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:41:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 21:44:45 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stddef.h>

/*This is the part where we look for expandable arguments in double quoted
sequences.
We split the sequence into an array of words based on '$' characters, replace
the $args by their value and strjoin them back into one string. Note that the
spaces are NOT removed in the process, they are seen as a character just like
any other.*/
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

static char	*get_next_word(char *seq, size_t *pos)
{
	size_t	i;
	int		in_arg;
	char	*ret;

	i = *pos;
	in_arg = 0;
	if (seq[i++] == '$' && (ft_isalnum(seq[i + 1])))
		in_arg = 1;
	while (seq[i])
	{
		if (seq[i] == '$' && !ft_isalnum(seq[i + 1]))
			i++;
		if ((myisspace(seq[i]) && in_arg) || (seq[i] == '$') || !seq[i + 1])
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
		if (arr[i][0] == '$' && (isalnum(arr[i][1]) || arr[i][1] == '?'))
			arr[i] = replace(arr[i], data);
	}
	arr[i] = NULL;
	return (arr);
}
static char	*expand_exitcode(char *str, t_shell *data)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (str[i])
	{
		if (ft_strnstr(&str[i], "$?", 2))
		{
			temp = ft_strndup(str, i);
			if (!temp)
				return (NULL);
			temp = ft_strjoin(temp, ft_itoa(data->exit));
			if (!temp)
				return (NULL);
			i += 2;
			str = ft_strjoin(temp, &str[i]);
			if (!str)
			return (free(temp), NULL);
		}
		i++;
	}
	return (str);
}

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
		node->sequence = expand_exitcode(data->temp, data);
	}
	return (free_array_arrsize(arr, size), 0);
}
