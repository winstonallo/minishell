/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:20:09 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/16 15:22:54 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_shell *data, char *path, int stdin_fd, int *pipe_fd)
{
	if (find_command(data) == 0)
	{
		close(stdin_fd);
		if (pipe_fd)
			close(pipe_fd[1]);
		if (path)
			free(path);
		wipe4real(data);
		exit(data->exit);
	}
	return (0);
}

/**
 * The function "find_path" searches for the executable file specified by the 
 * "command" parameter in the directories listed in the "data->paths" linked 
 * list, and returns the full path to the executable if found.
 * 
 * @param command The `command` parameter is a string that represents the name
 * of the command that we are trying to find the path for.
 */
char	*find_path(t_shell *data, char *command)
{
	t_path	*head;
	char	*temp;

	head = *data->paths;
	if (access(command, X_OK) == 0)
		return (command);
	command = ft_strjoin("/", command);
	if (!command)
		return (NULL);
	while (head)
	{
		temp = ft_strjoin(head->path, command);
		if (!temp)
			return (NULL);
		if (access(temp, X_OK) == 0)
			return (free(command), temp);
		free(temp);
		head = head->next;
	}
	free(command);
	return (NULL);
}

int	count_pipes(t_shell *data)
{
	t_cmd_table	*head;
	int			pipes;

	pipes = 0;
	head = *data->cmd_table;
	while (head)
	{
		if (head->pipe)
			pipes++;
		head = head->next;
	}
	return (pipes);
}
