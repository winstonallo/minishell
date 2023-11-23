/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:08:07 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/23 00:24:04 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "replace" takes a string and a shell data structure as input, 
 * and replaces a specific substring in the string with a corresponding
 * value from the shell's environment list.
 * 
 * @param str A pointer to a character array (string) that needs to be replaced.
 * @param data The "data" parameter is of type "t_shell" and is a pointer to a 
 * structure that contains information about the shell.
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

static int	do_expand(t_quotes *node, t_shell *data, size_t i, size_t pos)
{
	size_t	size;
	char	**arr;
	char	*temp;

	arr = fill_array(&size, node->sequence, &pos, data);
	if (!arr)
		return (-1);
	temp = NULL;
	while (++i < size)
	{
		if (!temp)
			temp = ft_strndup(arr[i], ft_strlen(arr[i]));
		else
			temp = ft_strjoin(node->sequence, arr[i]);
		if (!temp)
			return (free_array_arrsize(arr, size), -1);
		free(node->sequence);
		node->sequence = expand_exitcode(temp, data, 0);
	}
	return (free_array_arrsize(arr, size), 0);
}

/**
 * The function "expand_sequences" expands sequences within a shell data 
 * structure, including expanding double quotes and unquoted sequences.
 * 
 * @param data The parameter `data` is of type `t_shell*`, which is a pointer
 *  to a structure `t_shell`.
 * @return the value of `data->exit`.
 */
int	expand(t_shell *data)
{
	t_quotes	*head;

	head = *data->sequences;
	while (head)
	{
		if (head->status == IN_DOUBLE_QUOTES || head->status == UNQUOTED)
		{
			if (do_expand(head, data, -1, 0) == -1)
				return (-1);
		}
		head = head->next;
	}
	return (data->exit);
}
