/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:43:40 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/02 18:44:25 by sstanfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧
//BAUSTELLE IN: compare_env GEHT NOCH NICHT
//🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧
int strrrrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	compare_env(t_shell *data, char **new_line)
{
	t_env	*temp;

	temp = *data->env_list;
	// printf("len_ newline[0] : %i\n", strrrrlen(new_line[0]));
	// printf("len_ newline[1] : %i\n", strrrrlen(new_line[1]));
	while (temp)
	{
		if (ft_strncmp(temp->name, new_line[0], ft_strlen(temp->name) == 0)
			&& ft_strncmp(temp->line, new_line[1], ft_strlen(temp->line) == 0))
		{
			printf("here?");
			return (0);
		}
		// printf("name      :	%s\n", temp->name);
		// printf("name_len  : %i\n", strrrrlen(temp->name));
		// printf("line      : %s\n", temp->line);
		// printf("line_len  : %i\n", strrrrlen(temp->line));
		temp = temp->next;
	}
	return (1);
}

int	add_arg_to_env(t_shell *data, char **new_line)
{
	t_env	*new_node;
	t_env	*head;

	head = *data->env_list;
	new_node = envnew(new_line[0], new_line[1], ft_strlen(new_line[1]));
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

int	search_num_of_args(t_shell *data)
{
	int	i;

	i = 1;
	while ((*data->cmd_table)->args[i])
		i++;
	return (i);
}
int	update_env_list(t_shell *data)
{
	char	**new_line;
	int		len;
	int		i;

	len = search_num_of_args(data);
	i = 1;
	while (i <= len)
	{
		new_line = ft_split((*data->cmd_table)->args[i], '=');
		if (!new_line)
			return (-1);
		if (compare_env(data, new_line) == 0)
		{
			free(new_line[1]);
			free(new_line);
			i++;
			continue ;
		}
		if (add_arg_to_env(data, new_line) == -1)
			return (-1);
		free(new_line[1]);
		free(new_line);
		i++;
	}
	return (0);
}
