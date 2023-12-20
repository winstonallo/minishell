/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:43:40 by sstanfel          #+#    #+#             */
/*   Updated: 2023/12/20 11:37:58 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	strrrrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	maxlen(char **new_line, char *name)
{
	int	max_len;

	if (ft_strlen(new_line[0]) > ft_strlen(name))
		max_len = ft_strlen(new_line[0]);
	else
		max_len = ft_strlen(name);
	return (max_len);
}

/**
 * The function `compare_env` compares the name of an environment variable with
 *  a given string and updates its value if a match is found.
 * 
 * @param new_line A pointer to an array of strings, where new_line[0] is the 
 * name of an environment
 * variable and new_line[1] is the new value for that variable.
 */
int	compare_env(t_shell *data, char **new_line)
{
	t_env	*temp;
	int		max_len;

	temp = *data->env_list;
	max_len = maxlen(new_line, temp->name);
	while (temp)
	{
		if ((ft_strncmp(temp->name, new_line[0], max_len)) == 0)
		{
			free(temp->line);
			temp->line = ft_strdup(new_line[1]);
			if (!temp->line)
				return (-1);
			return (update_paths(data, temp->line), 1);
		}
		temp = temp->next;
	}
	if (update_paths(data, new_line[0]) == -1)
		return (-1);
	return (0);
}

/**
 * The function `add_arg_to_env` adds a new environment variable to a 
 * linked list of environment variables.
 * @param new_line A pointer to an array of strings, where the first element is
 * the key and the second element is the value to be added to the environment.
 */
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

/**
 * The function `update_env_list` updates the environment list 
 * in a shell program by adding a new environment variable.
 */
int	update_env_list(t_shell *data)
{
	char	**new_line;

	new_line = ft_split((*data->cmd_table)->args[1], '=');
	if (!new_line)
		return (-1);
	if (compare_env(data, new_line) == 1)
		return (free_array(new_line), 0);
	else if (compare_env(data, new_line) == -1)
		return (-1);
	if (add_arg_to_env(data, new_line) == -1)
		return (-1);
	free_array(new_line);
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
