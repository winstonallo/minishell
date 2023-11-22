/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_cmd_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:51:30 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/22 21:30:18 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*List utils functions, just need different ones based on list name & content*/
t_cmd_table	*cmdnew(int outfile, int infile, int pepi)
{
	t_cmd_table	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->path = NULL;
	new->outfile = outfile;
	new->infile = infile;
	new->pipe = pepi;
	new->next = NULL;
	return (new);
}

void	cmdadd_back(t_cmd_table **lst, t_cmd_table *new_node)
{
	t_cmd_table	*current;

	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

void	free_cmd_tables(t_cmd_table **cmd_tables)
{
	t_cmd_table	*head;
	t_cmd_table	*temp;

	if (!cmd_tables)
		return ;
	head = *cmd_tables;
	while (head)
	{
		temp = head;
		if (head->args)
			free_array(head->args);
		if (head->path)
			free(head->path);
		if (head->infile > 0)
			close(head->infile);
		if (head->outfile > 0)
			close(head->outfile);
		head = head->next;
		free(temp);
	}
	free(cmd_tables);
}
