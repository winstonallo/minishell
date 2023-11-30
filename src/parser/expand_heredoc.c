/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 04:54:55 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 06:29:34 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_unexpanded_value(char *str, t_shell *data)
{
	t_env	*head;

	head = *data->env_list;
	while (head)
	{
		if (!ft_strncmp(str, head->line, ft_strlen(str) + 1))
		{
			str = ft_strjoin("$", head->name);
			if (!str)
				return (NULL);
			break ;
		}
		head = head->next;
	}
	return (str);
}

char	*expand_heredoc(t_shell *data, char *line)
{
	size_t	size;
	char	**arr;
	char	*temp;
	size_t	i;
	size_t	pos;

	pos = 0;
	i = -1;
	arr = fill_array(&size, line, &pos, data);
	if (!arr)
		return (NULL);
	temp = NULL;
	while (++i < size)
	{
		if (!temp)
			temp = ft_strndup(arr[i], ft_strlen(arr[i]));
		else
			temp = ft_strjoin(line, arr[i]);
		if (!temp)
			return (free_array_arrsize(arr, size), NULL);
		free(line);
		line = expand_exitcode(temp, data, 0);
	}
	return (free_array_arrsize(arr, size), line);
}
