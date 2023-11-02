/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:22:46 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/02 15:29:29 by sstanfel         ###   ########.fr       */
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
		return (-1);
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

int	export(t_shell *data)
{
	if (ft_strncmp((*data->cmd_table)->args[1], "=", 1) == 0)
		return (-1);
	else if (update_env_list(data) != 0)
		return (-1);
	return (0);
}
#include <unistd.h>

int	cd(t_shell *data)
{
	if (chdir((*data->cmd_table)->args[1]) == -1)
	{
		perror("minishell: cd");
		return (-1);
	}
	get_prompt(data);
	return (0);
}

int	pwd(t_shell *data)
{
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return (-1);
	printf("%s\n", data->cwd);
	return (0);
}
