/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:33:12 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/12 19:08:25 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

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

static int	child2(t_cmd_table *head, t_shell *data)
{
	pid_t	pid;
	int		status;

	head->path = find_path(data, head->args[0]);
	if (!head->path)
		return (-1);
	pid = fork();
	if (!pid)
	{
		execve(head->path, head->args, data->environment);
		ft_putstr_fd(data->command_path, 2);
		perror(": failed to execute command");
		wipe(data);
		exit (1);
	}
	waitpid(pid, &status, 0);
	free(head->path);
	//if (!data->exit)
	data->exit = WEXITSTATUS(status);
	return (0);
}

/**
 * The function `child_process` creates a child process, redirects input and 
 * output if necessary and executes a command while the parent waits.
 * 
 */
void	child1(t_cmd_table *head, t_shell *data)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit (0);
	pid = fork();
	if (!pid)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		execve(head->path, head->args, data->environment);
		close(pipe_fd[1]);
		ft_putstr_fd(data->command_path, 2);
		perror("minishell: failed to execute command");
		wipe(data);
		exit(1);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		int status;
		waitpid(pid, &status, WNOHANG);
		//if (!data->exit)
		data->exit = WEXITSTATUS(status);
	}
}

static int	count_pipes(t_shell *data)
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

/**
 * The function executes a command by finding its path, creating a child 
 * process, and freeing the command path.
 */
int	execute_command(t_shell *data)
{
	t_cmd_table	*head;
	int			pipes;
	int			i;
	int			stdin_fd;

	stdin_fd = dup(0);
	i = -1;
	head = *data->cmd_table;
	pipes = count_pipes(data);
	while (++i < pipes)
	{
		head->path = find_path(data, head->args[0]);
		if (!head->path)
			return (-1);
		child1(head, data);
		free(head->path);
		head = head->next;
		if (head && head->pipe)
			head = head->next;
	}
	if (child2(head, data) == -1)
		return (-1);
	dup2(stdin_fd, 0);
	close(stdin_fd);
	return (0);
}
