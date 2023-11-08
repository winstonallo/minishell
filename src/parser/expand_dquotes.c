/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:41:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 10:56:36 by abied-ch         ###   ########.fr       */
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
static size_t	count_words(char *seq, int i, int ret)
{
	while (seq[i])
	{
		if (seq[i] == '$' && myisspace(seq[i + 1]))
		{
			i += 2;
			ret--;
		}	
		if (seq[i] == '$')
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
	int		endofseq = 0;

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
			if (seq [i] != ' ' && !seq[i + 1])
				endofseq++;
			ret = ft_strndup(&seq[*pos], (i + endofseq) - *pos);
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
		if (arr[i][0] == '$' && arr[i][1] && isalnum(arr[i][1]))
			arr[i] = replace(arr[i], data);
	}
	arr[i] = NULL;
	return (arr);
}

char	*expand_dquotes(char *sequence, t_shell *data, size_t i, size_t pos)
{
	size_t	size;
	char	**arr;
	char	*new_temp;

	size = count_words(sequence, 0, 0);
	arr = fill_array(size, sequence, &pos, data);
	if (!arr)
		return (NULL);
	while (++i < size)
	{
		if (!data->temp)
			new_temp = ft_strndup(arr[i], ft_strlen(arr[i]));
		else
			new_temp = ft_strjoin(data->temp, arr[i]);
		if (!new_temp)
		{
			free_array(arr);
			return (NULL);
		}
		free(data->temp);
		data->temp = new_temp;
	}
	return (free_array_arrsize(arr, size), data->temp);
}
