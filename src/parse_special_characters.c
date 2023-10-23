/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special_characters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:35:55 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/23 22:15:19 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stddef.h>

int	isop(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INPUT_REDIRECTION);
	else if (c == '>')
		return (OUTPUT_REDIRECTION);
	return (0);
}

// static size_t	get_word_len(char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (!isop(s[i]))
// 		i++;
// 	return (i);
// }

/*🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧
memory management if fail after first iteration*/
int split_curr_sequence(char *seq, t_shell *data)
{
	size_t	i;
	size_t	j;
	t_op	*new;
	
	i = -1;
	j = 0;
	data->operators = malloc(sizeof(data->operators));
	if (!data->operators)
		return (-1);
	*data->operators = NULL;
	while(seq[++i])
	{
		i = j;
		while (!isop(seq[j]) && seq[j])
		{
			j++;	
			if (isop(seq[j]) || !seq[j])
			{
				new = opnew(&seq[i], UNQUOTED, 0, j - i);
				if (!new)
					return (-1);
				opadd_back(data->operators, new);
			}
		}
		if (isop(seq[j]))
		{
			new = opnew(NULL, SPECIAL_CHAR, isop(seq[j]), 0);
			if (!new)
				return (-1);
			opadd_back(data->operators, new);
			j++;
		}
	}
	return (0);
}


int parse_special_char(t_shell *data)
{
	t_quotes	*temp;
	
	temp = *data->sequences;
	while(temp)
	{
		if (split_curr_sequence(temp->sequence, data) == -1)
			return (-1);
		temp = temp->next;	
	}
	return(0);
}