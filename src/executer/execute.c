/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:33:12 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/16 15:30:58 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	child2(t_cmd_table *head, t_shell *data, int stdin_fd)
{
	pid_t	pid;
	int		status;

	head->path = find_path(data, head->args[0]);
	if (!head->path)
		return (-1);
	pid = fork();
	if (!pid)
	{
		if (head->outfile != NO_FD)
			dup2(head->outfile, 1);
		if (head->infile != NO_FD)
			dup2(head->infile, 0);
		is_builtin(data, head->path, stdin_fd, NULL);
		execve(head->path, head->args, data->environment);
		ft_putstr_fd(data->command_path, 2);
		perror(": failed to execute command");
		wipe(data);
		exit (1);
	}
	waitpid(pid, &status, 0);
	free(head->path);
	data->exit = WEXITSTATUS(status);
	return (0);
}

/**
 * The function `child_process` creates a child process, redirects input and 
 * output if necessary and executes a command while the parent waits.
 * 
 */
void	child1(t_cmd_table *head, t_shell *data, int stdin_fd)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit (0);
	pid = fork();
	if (!pid)
	{
		close(pipe_fd[0]);
		if (head->outfile != NO_FD)
			dup2(head->outfile, 1);
		else
			dup2(pipe_fd[1], 1);
		if (head->infile != NO_FD)
			dup2(head->infile, 0);
		is_builtin(data, head->path, stdin_fd, pipe_fd);
		execve(head->path, head->args, data->environment);
		close(pipe_fd[1]);
		ft_putstr_fd(data->command_path, 2);
		perror("minishell: failed to execute command");
		wipe(data);
		exit(1);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
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
		child1(head, data, stdin_fd);
		free(head->path);
		head = head->next;
		if (head && head->pipe)
			head = head->next;
	}
	if (child2(head, data, stdin_fd) == -1)
		return (close(stdin_fd), -1);
	dup2(stdin_fd, 0);
	close(stdin_fd);
	return (0);
}
