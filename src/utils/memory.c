/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:17 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/02 14:43:23 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Memory management utils*/
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
		if (head->infile != NO_FD)
			close(head->infile);
		if (head->outfile != NO_FD)
			close(head->outfile);
		head = head->next;
		free(temp);
	}
	free(cmd_tables);
}

void	free_environment(t_env **env)
{
	t_env	*head;
	t_env	*temp;

	head = *env;
	while (head)
	{
		temp = head;
		if (temp->line)
			free(temp->line);
		if (temp->name)
			free(temp->name);
		head = head->next;
		free(temp);
	}
	free(env);
}

void	wipe(t_shell *data)
{
	if (data->raw_input)
		free(data->raw_input);
	free_opps(data->operators);
	free_sequences(data->sequences);
	free_cmd_tables(data->cmd_table);
}
