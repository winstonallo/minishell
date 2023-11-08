/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:43:40 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/08 14:03:58 by sstanfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



int	compare_env(t_shell *data, char **new_line)
{
	t_env	*temp;
	int		max_len;

	temp = *data->env_list;
	if (ft_strlen(new_line[0]) > ft_strlen(temp->name))
		max_len = ft_strlen(new_line[0]);
	else
		max_len = ft_strlen(temp->name);
	while (temp)
	{
		if ((ft_strncmp(temp->name, new_line[0], max_len)) == 0)
		{
			free(temp->line);
			temp->line = ft_strdup(new_line[1]);
			if (!temp->line)
				return (-1);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	add_arg_to_env(t_shell *data, char **new_line)
{
	t_env	*new_node;
	t_env	*head;

	head = *data->env_list;
	new_node = envnew(ft_strdup(new_line[0]), new_line[1],
			ft_strlen(new_line[1]));

	if (!new_node)
		return (-1);
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
	return (0);
}


int	update_env_list(t_shell *data)
{
	char	**new_line;
	//int		len;
	//int		i;

	//len = ft_strlen((*data->cmd_table)->args[1]);
	//i = 1;
	//while (i < len)
	//{
		new_line = ft_split((*data->cmd_table)->args[1], '=');
		if (!new_line)
			return (-1);
		if (compare_env(data, new_line) == 1)
		{
			free_array(new_line);
			//i++;
			//continue ;
		}
		else if (compare_env(data, new_line) == -1)
			return (-1);
		if (add_arg_to_env(data, new_line) == -1)
			return (-1);
		//i++;
		free_array(new_line);
	//}
	return (0);
}
