/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:14:45 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 20:04:05 by abied-ch         ###   ########.fr       */
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
	while (head && head->special_character != PIPE)
	{
		arr[++i] = ft_strdup(head->sequence);
		if (!arr[i])
			return (free_array(arr), NULL);
		head = head->next;
	}
	arr[++i] = NULL;
	return (arr);
}

int	get_command_table_list(t_shell *data)
{
	t_cmd_table	*new;
	t_op		*head;
	char		*infile;
	char		*outfile;

	data->cmd_table = malloc(sizeof(data->cmd_table));
	if (!data->cmd_table)
		return (-1);
	*data->cmd_table = NULL;
	head = *data->operators;
	while (head->special_character != PIPE && head)
	{
		if (head->special_character == OUTPUT_REDIRECTION)
			outfile = head->next->sequence;
		else if (head->special_character == INPUT_REDIRECTION)
			infile = head->next->sequence;
	}
	
}

int	get_command_table(t_shell *data)
{

	if (!arr)
		return (-1);
	
	for (int i = 0; arr[i]; i++)
		printf("cmd arg nr.%d: %s\n", i, arr[i]);
	return (0);	
}
