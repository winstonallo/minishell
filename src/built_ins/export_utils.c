/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:43:40 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/05 17:55:44 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_env_list(t_shell *data)
{
	char	**new_line;
	t_env	*new_node;
	t_env	*head;

	head = *data->env_list;
	new_line = ft_split((*data->cmd_table)->args[1], '=');
	if (!new_line)
		return (data->exit);
	new_node = envnew(new_line[0], new_line[1], ft_strlen(new_line[1]));
	if (!new_node)
		return (data->exit);
	envadd_back(data->env_list, new_node);
	if (!new_line)
		return (-1);
	while (head)
	{
		if (head->next == NULL)
		{
			head->next = new_node;
			new_node->next = NULL;
			break ;
		}
		head = head->next;
	}
	return (free(new_line[1]), free(new_line), data->exit);
}
