/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_cmd_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:51:30 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/03 11:02:44 by abied-ch         ###   ########.fr       */
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
	new->outfile = outfile;
	if (new->outfile == -1)
		return (NULL);
	new->infile = infile;
	if (new->infile == -1)
		return (close(new->outfile), NULL);
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
