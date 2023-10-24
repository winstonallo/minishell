/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:14:45 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 19:37:42 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_command_array(t_shell *data)
{
	t_op	*head;
	int		i;
	char	**arr;
	
	i = 0;
	head = *data->operators;
	while (head && !head->special_character)
	{
		i++;
		head = head->next;
	}
	arr = malloc((i + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	head = *data->operators;
	i = -1;
	while (head && !head->special_character)
	{
		arr[++i] = ft_strdup(head->sequence);
		if (!arr[i])
			return (free_array(arr), NULL);
		head = head->next;
	}
	arr[++i] = NULL;
	return (arr);
}

int	get_command_table(t_shell *data)
{
	char	**arr;

	arr = get_command_array(data);
	for (int i = 0; arr[i]; i++)
		printf("cmd arg nr.%d: %s\n", i, arr[i]);
	return (0);	
}
