/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_cmd_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:51:30 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/23 15:13:06 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*List utils functions, just need different ones based on list name & content*/
t_cmd_table	*cmdnew(int outfile, int infile, int pepi, char	*eof)
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
	new->heredoc = eof;
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
	else if (!*cmd_tables)
		return (free(cmd_tables));
	head = *cmd_tables;
	while (head)
	{
		temp = head;
		if (head->args)
			free_array(head->args);
		freeze(head->path);
		freeze(head->heredoc);
		if (head->infile > 0)
			close(head->infile);
		if (head->outfile > 0)
			close(head->outfile);
		head = head->next;
		free(temp);
	}
	free(cmd_tables);
}
