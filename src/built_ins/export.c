/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:52:25 by arthur            #+#    #+#             */
/*   Updated: 2023/11/30 10:37:16 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_sorted_env(t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp)
	{
		printf("declare -x %s=%s\n", temp->name, temp->line);
		temp = temp->next;
	}
}

t_env	*get_next_node(t_env **list, t_env *last)
{
	t_env	*head;
	t_env	*next;

	next = NULL;
	head = *list;
	while (head)
	{
		if (strcmp(head->name, last->name) > 0)
		{
			if (next == NULL || strcmp(head->name, next->name) < 0)
				next = head;
		}
		head = head->next;
	}
	if (!next)
		return (NULL);
	return (envnew(ft_strdup(next->name), next->line, ft_strlen(next->line)));
}

t_env	*get_smallest_node(t_env **list)
{
	t_env	*head;
	t_env	*smallest;

	smallest = NULL;
	head = *list;
	while (head)
	{
		if (smallest == NULL || strcmp(head->name, smallest->name) < 0)
			smallest = head;
		head = head->next;
	}
	if (!smallest)
		return (NULL);
	return (envnew(ft_strdup(smallest->name), smallest->line,
			ft_strlen(smallest->line)));
}

int	export_env(t_shell *data)
{
	t_env	*new;
	int		i;
	int		size;

	i = 0;
	new = get_smallest_node(data->env_list);
	if (!new)
		return (-1);
	size = envsize(data->env_list);
	envadd_back(data->sorted_env, new);
	while (++i <= size)
	{
		new = get_next_node(data->env_list, new);
		if (!new)
			break ;
		envadd_back(data->sorted_env, new);
	}
	return (0);
}

int	export(t_shell *data)
{
	int		i;
	char	**arg;
	int		argname;

	i = 0;
	arg = (*data->cmd_table)->args;
	if ((*data->cmd_table)->next)
		return (COMMAND_NOT_FOUND);
	if (!arg[1])
	{
		print_sorted_env(data->sorted_env);
		return (SUCCESS);
	}
	argname = 1;
	while (arg[++i])
	{
		if (export_error(arg[i], argname) == 1)
			return (data->exit = FAILURE);
		else if (export_error(arg[i], argname) == 2)
			return (data->exit = SUCCESS);
		else if (update_env_list(data) != 0)
			return (data->exit = FAILURE);
		argname = 0;
	}
	return (SUCCESS);
}
