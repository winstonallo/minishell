/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:47:41 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 04:34:37 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_arg(t_shell *data, char *arg)
{
	t_env	*head;
	t_env	*temp;

	temp = NULL;
	head = *data->env_list;
	if (head != NULL && !ft_strncmp(arg, head->name, ft_strlen(arg) + 1))
	{
		*data->env_list = head->next;
		free(head->name);
		free(head->line);
		free(head);
		return ;
	}
	while (head != NULL && ft_strncmp(arg, head->name, ft_strlen(arg) + 1) != 0)
	{
		temp = head;
		head = head->next;
	}
	if (head == NULL)
		return ;
	temp->next = head->next;
	free(head->name);
	free(head->line);
	free(head);
}

void	unset(t_shell *data)
{
	int	i;

	i = 0;
	while ((*data->cmd_table)->args[++i])
		remove_arg(data, (*data->cmd_table)->args[i]);
	i = 0;
	while ((*data->cmd_table)->args[++i])
	{
		if (!ft_strncmp((*data->cmd_table)->args[i], "PATH",
				ft_strlen("PATH") + 1))
			update_paths(data, (*data->cmd_table)->args[i]);
	}
}
