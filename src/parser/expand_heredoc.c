/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 04:54:55 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 09:00:49 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_unexpanded_value(char *str, t_shell *data)
{
	t_env	*head;
	char	*temp;

	temp = NULL;
	head = *data->env_list;
	while (head)
	{
		if (!ft_strncmp(str, head->line, ft_strlen(str) + 1))
		{
			temp = ft_strjoin("$", head->name);
			if (!temp)
				return (NULL);
			break ;
		}
		head = head->next;
	}
	if (!temp)
		return (ft_strdup(str));
	return (temp);
}

char *expand_heredoc(t_shell *data, char *line, size_t i, size_t pos)
{
    size_t	size;
    char	**arr;
    char	*temp;
	char	*new_temp;

    arr = fill_array(&size, line, &pos, data);
    if (!arr)
        return NULL;
    temp = NULL;
    while (++i < size)
	{
        if (!temp)
            temp = ft_strndup(arr[i], ft_strlen(arr[i]));
        else 
		{
            new_temp = ft_strjoin(temp, arr[i]);
            free(temp);
            temp = new_temp;
        }
        if (!temp)
            return (free_array_arrsize(arr, size), NULL);
        free(arr[i]);
    }
    free(arr);
    return temp;
}

