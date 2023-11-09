/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:31:47 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:46:52 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The `env` function prints the environment variables stored in a linked list.
 * 
 * @param data The parameter "data" is of type "t_shell*", which is a pointer to a structure of type
 * "t_shell".
 * 
 * @return the value of `data->exit`.
 */
int	env(t_shell *data)
{
	t_env	*head;

	head = *data->env_list;
	while (head)
	{
		printf("%s=%s\n", head->name, head->line);
		head = head->next;
	}
	data->exit = 0;
	return (data->exit);
}
