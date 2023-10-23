/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special_characters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:35:55 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/23 20:51:59 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

/*🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧
memory management if fail after first iteration*/
int split_curr_sequence(char *seq, t_shell *data)
{
	size_t	i;
	t_op	*new;
	
	i = -1;
	data->operators = malloc(sizeof(data->operators));
	if (!data->operators)
		return (-1);
	*data->operators = NULL;
	while(seq[++i])
	{
		if(isop(seq[i]) || !seq[i])
		{
			if (i > 0)
			{
				new = opnew(seq, UNQUOTED, 0, i);
				if (!new)
					return (-1);
				opadd_back(data->operators, new);				
			}
			if (isop(seq[i]))
			{
				new = opnew(&seq[i], SPECIAL_CHAR, isop(seq[i]), 1);
				if (!new)
					return (-1);
				opadd_back(data->operators, new);		
			}
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