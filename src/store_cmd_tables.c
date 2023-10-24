/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cmd_tables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:51:30 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 19:55:27 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd_table	*cmdnew(char **args, char *outfile, char *infile, int pepi)
{
	t_cmd_table	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->args = args;
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