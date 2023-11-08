/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:08:07 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 10:22:28 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*This is the second step of the parsing process.
We go through the whole list of sequences and look for '$' in 
double- and unquoted sequences (the single quotes escape it).
If we find a '$', we look for it in the environment, and if we find it, we
replace it with its value, otherwise, we remove the argument
(echo $nonexistingargument prints only a newline)*/
char	*replace(char *str, t_shell *data)
{
	char	*ret;
	t_env	*head;

	head = *data->env_list;
	str++;
	if (*str == '?')
	{
		ret = ft_itoa(data->exit);
		if (!ret)
			return (NULL);
		return (free(--str), ret);
	}
	while (head)
	{
		if (ft_strncmp(str, head->name, ft_strlen(str)) == 0)
		{
			ret = ft_strdup(head->line);
			if (!ret)
				return (NULL);
			return (free(--str), ret);
		}
		head = head->next;
	}
	return (free(--str), ft_strdup(""));
}

int	expand_sequences(t_shell *data)
{
	t_quotes	*head;
	char		*temp;

	head = *data->sequences;
	while (head)
	{
		if (head->status == IN_DOUBLE_QUOTES)
		{
			temp = head->sequence;
			head->sequence = expand_dquotes(head->sequence, data, -1, 0);
			if (!head->sequence)
				return (data->exit = FAILURE);
			free(temp);
		}
		else if (head->status == UNQUOTED)
		{
			head->sequence = expand_uquotes(head->sequence, data);
			if (!head->sequence)
				return (data->exit = FAILURE);
		}
		head = head->next;
	}
	return (data->exit);
}
