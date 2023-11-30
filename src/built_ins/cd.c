/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:29:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 02:57:33 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_old_pwd(t_shell *data, char *oldpwd)
{
	t_env	*head;
	
	head = *data->env_list;
	while (head)
	{
		if (!ft_strncmp(head->name, "OLDPWD", ft_strlen(head->name) + 1))
		{
			freeze(head->line);
			head->line = ft_strdup(oldpwd);
			if (!head->line)
				return (FAILURE);
		}
		head = head->next;
	}
	return (SUCCESS);
}

int	update_pwd(t_shell *data)
{
	t_env	*head;

	head = *data->env_list;
	while (head)
	{
		if (!ft_strncmp(head->name, "PWD", ft_strlen(head->name) + 1))
		{
			update_old_pwd(data, head->line);
			freeze(head->line);
			head->line = getcwd(NULL, 0);
			if (!head->line)
				return (FAILURE);
		}
		head = head->next;
	}
	return (SUCCESS);
}

static char	*get_homedir(t_shell *data)
{
	t_env	*head;

	head = *data->env_list;
	while (head)
	{
		if (ft_strncmp(head->name, "HOME", 5) == 0)
			return (head->line);
		head = head->next;
	}
	return (NULL);
}

/**
 * The function `cd` changes the current directory in a shell program and 
 * updates the prompt.
 * @return either SUCCESS or FAILURE.
 */
int	cd(t_shell *data, int i)
{
	while ((*data->cmd_table)->args[i])
		i++;
	if (i > 2)
	{
		data->exit = FAILURE;
		return (ft_putstr_fd("cd: too many arguments\n", 2), FAILURE);
	}
	else if (i == 1 || !ft_strncmp((*data->cmd_table)->args[1], "~", 2))
	{
		if (chdir(get_homedir(data)) == -1)
		{
			perror("minishell: cd");
			data->exit = FAILURE;
			return (FAILURE);
		}
	}
	else if (chdir((*data->cmd_table)->args[1]) == -1)
	{
		perror("minishell: cd");
		data->exit = FAILURE;
		return (FAILURE);
	}
	if (get_prompt(data, 0) == -1)
		return (FAILURE);
	return (SUCCESS);
}
