/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:20:09 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 04:39:21 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

void	exit_handler(t_shell *data, DIR *check, t_cmd_table *head)
{
	if (data->exit == COMMAND_NOT_FOUND)
	{
		if (head->args && head->args[0])
		{
			ft_putstr_fd(head->args[0], 2);
			ft_putendl_fd(": command not found", 2);
		}
		else
			data->exit = 0;
	}
	if (head->infile >= 0 && head->infile != HEREDOCINT)
		close(head->infile);
	unlink(".temp_heredoc");
	close(data->stdin_fd);
	wipe4real(data);
	if (check)
		closedir(check);
	exit(data->exit);
}

void	close_pipe_init_fd(int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

int	is_builtin(t_shell *data, t_cmd_table *head, int *pipe_fd)
{
	if (head->infile != HEREDOCINT)
		data->exit = find_command(data, head);
	if (data->exit == SUCCESS)
	{
		close(data->stdin_fd);
		if (pipe_fd)
		{
			close(pipe_fd[1]);
			close(pipe_fd[0]);
		}
		wipe4real(data);
		exit(data->exit);
	}
	return (data->exit);
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
	data->validpath = 0;
	if (!command)
		return (NULL);
	if (access(command, X_OK | R_OK) == 0)
		return (data->validpath = 1, ft_strdup(command));
	command = ft_strjoin("/", command);
	if (!command)
		return (NULL);
	while (head)
	{
		temp = ft_strjoin(head->path, command);
		if (!temp)
			return (data->validpath = MALLOC_ERROR, NULL);
		if (access(temp, X_OK | R_OK) == 0)
			return (data->validpath = 1, free(command), temp);
		free(temp);
		head = head->next;
	}
	free(command);
	data->validpath = 0;
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
