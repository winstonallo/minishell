/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:08:07 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:59:06 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "replace" takes a string and a shell data structure as input, and replaces a specific
 * substring in the string with a corresponding value from the shell's environment list.
 * 
 * @param str A pointer to a character array (string) that needs to be replaced.
 * @param data The "data" parameter is of type "t_shell" and is a pointer to a structure that contains
 * information about the shell.
 * 
 * @return The function `replace` returns a `char*`.
 */
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

/**
 * The function "expand_sequences" expands sequences within a shell data structure, including expanding
 * double quotes and unquoted sequences.
 * 
 * @param data The parameter `data` is of type `t_shell*`, which is a pointer to a structure `t_shell`.
 * 
 * @return the value of `data->exit`.
 */
int	expand_sequences(t_shell *data)
{
	t_quotes	*head;

	head = *data->sequences;
	while (head)
	{
		if (head->status == IN_DOUBLE_QUOTES)
		{
			if (expand_dquotes(head, data, -1, 0))
				return (-1);
		}
		else if (head->status == UNQUOTED)
		{
			head->sequence = expand_uquotes(head->sequence, data);
			if (!head->sequence)
				return (-1);
		}
		head = head->next;
	}
	return (data->exit);
}
