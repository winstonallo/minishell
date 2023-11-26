/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:47:41 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/26 22:44:53 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void remove_arg(t_shell *data, char *arg)
{
    t_env *head;
    t_env *temp;
    t_env *to_remove;

    head = *data->env_list;
    temp = NULL; // Initialize temp to NULL
    while (head)
    {
        if (!ft_strncmp(arg, head->name, ft_strlen(arg) + 1))
        {
            to_remove = head;
            if (temp)
                temp->next = to_remove->next;
            else
                *data->env_list = to_remove->next; // Update the head if removing the first node
            free(to_remove);
            return; // Assuming there's only one matching entry
        }
        temp = head;
        head = head->next;
    }
}


void	unset(t_shell *data)
{
	int	i;

	i = 0;
	while ((*data->cmd_table)->args[++i])
		remove_arg(data, (*data->cmd_table)->args[i]);
}
