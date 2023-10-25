/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:17 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/25 14:46:44 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd_tables(t_cmd_table **cmd_tables)
{
	t_cmd_table	*head;
	t_cmd_table	*temp;

	head = *cmd_tables;
	while (head)
	{
		temp = head;
		if (head->args)
			free_array(head->args);
		head = head->next;
		free(temp);
	}
	free(cmd_tables);
}

void	wipe(t_shell *data)
{
	if (data->raw_input)
		free(data->raw_input);
	free_opps(data->operators);
	free_sequences(data->sequences);
	free_cmd_tables(data->cmd_table);
}
