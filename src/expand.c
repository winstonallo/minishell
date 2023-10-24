/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:41:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 13:47:10 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t count_words(char *seq)
{
    int i;
    int ret;

    i = 0;
    ret = 0;
    while (seq[i])
    {
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

static char *get_next_word(char *seq, size_t *pos)
{
    size_t  i;
    int     in_arg;
    char    *ret;

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
    return (NULL);
}

char	*replace(char *str, t_shell *data)
{
	char	*arg;

	arg = ft_strndup("Hello", 6);
	if (!arg)
		return (NULL);
	if (data)
	{
		if (ft_strncmp(str, "$arg", 4) == 0)
			return (free(str), arg);	
	}
	return (NULL);
}

char    *expand_dquotes(char *sequence, t_shell *data)
{
    size_t      arr_size;
    char        **arr;
    size_t      i;
    size_t      pos;
	char		*temp;
	
	temp = NULL;
    i = -1;
    pos = 0;
    arr_size = count_words(sequence);
    arr = malloc((arr_size + 1) * sizeof(char *));
    if (!arr)
		return (NULL);
    while (++i < arr_size)
    {
        arr[i] = get_next_word(sequence, &pos);
        if (!arr[i])
            return (free(arr), NULL);
		if (arr[i][0] == '$' && isalnum(arr[i][1]))
			arr[i] = replace(arr[i], data);
    }
	i = -1;
	while (++i < arr_size)
	{
		if (!temp)
			temp = ft_strndup(arr[i], ft_strlen(arr[i]));
		else
		 	temp = ft_strjoin(temp, arr[i]);
		if (!temp)
			return (free_array(arr), NULL);
	}
	return (free_array_arrsize(arr, arr_size), free(sequence), temp);
}
/*🚧 NICHT WUNDERN WENN NIX FUNKTIONIEREN*/
void	expand_sequences(t_shell *data)
{
	t_quotes	*head;

	head = *data->sequences;
	while (head)
	{
		if (head->status == IN_DOUBLE_QUOTES)
			head->sequence = expand_dquotes(head->sequence, data);
		head = head->next;
	}
}
