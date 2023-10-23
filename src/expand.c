/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:41:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/23 11:43:55 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stddef.h>

// char *replace(char *current, size_t *i)
// {
//     char *temp;
//     char *new;
//     char *expanded_content;
	
// 	expanded_content = "EXPANSION CONTENT";
//     size_t index;
// 	index = *i;
//     temp = ft_strndup(current, index);
//     if (!temp)
//         return NULL;
//     while (current[index] && !myisspace(current[index]))
//         index++;
//     *i = index;
//     new = ft_strjoin(temp, expanded_content);
//     if (!new)
// 		return (free(temp), NULL);
// 	free(temp);
//     return new;
// }

// char *expand_dquotes(t_quotes *current)
// {
//     size_t i = 0;
//     char *new;
//     char *temp;

// 	new = NULL;
//     while (current->sequence[i])
//     {
//         if (current->sequence[i] == '$')
//         {
//             temp = replace(current->sequence, &i);
//             if (!temp)
//                 return NULL;
//             if (!new)
//                 new = temp;
//             else
//             {
//                 char *old_new = new;
//                 new = ft_strjoin(old_new, temp);
// 				if (!new)
// 					return (free(old_new), free(temp), NULL);
// 				printf("new after joining: %s\n i : %zu\n", new, i);

//                 free(old_new);
//                 free(temp);
//             }
//         }
//         else
//             i++;
//     }
//     if (!new)
//         return ft_strdup(current->sequence);
//     free(current->sequence);
//     return new;
// }

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
            while (seq[i] && seq[i] != '$' && !myisspace(seq[i]))
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
    size_t  i = *pos;
    int     in_arg = 0;
    char    *ret;

    if (seq[i] == '$')
    {
		in_arg = 1;
		i++;
	}    
    while (seq[i])
    {
        if ((myisspace(seq[i]) && in_arg) || (seq[i] == '$') || !seq[i + 1])
        {
            if (!seq[i + 1])
                i++;
            ret = ft_strndup(&seq[*pos], i - *pos);
            if (!ret)
                return (NULL);
            *pos = i;
            return ret;
        }
        i++;
    }
    return NULL;
}


char    *expand_dquotes(char *sequence)
{
    size_t		arr_size;
    char		**arr;
    size_t		i;
    size_t		pos;
    
    i = -1;
    pos = 0;
    arr_size = count_words(sequence);
    arr = malloc((arr_size + 1) * sizeof(char *));
    if (!arr)
        return (NULL);
    while (++i < arr_size)
    {
		printf("i = %zu\n", i);
        arr[i] = get_next_word(sequence, &pos);
		printf("array index %zu: %s\n", i, arr[i]);
		if (!arr[i])
			return(free_array(arr), NULL);
    }
    return (NULL);
}

/*TODO: idea for different expanding approach, see github issues*/
void	expand_sequences(t_shell *data)
{
	t_quotes	*head;

	head = *data->sequences;
	while (head)
	{
		if (head->status == IN_DOUBLE_QUOTES)
			head->sequence = expand_dquotes(head->sequence);
		head = head->next;
	}
}
