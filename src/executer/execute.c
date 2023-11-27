/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:33:12 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/27 14:50:43 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

static void	exit_handler(t_shell *data, int stdin_fd, DIR *check, int code)
{
	if (code)
		data->exit = code;
	close(stdin_fd);
	wipe4real(data);
	if (check)
		closedir(check);
	exit(data->exit);
}

static void	check_permission(t_shell *data, t_cmd_table *head, int stdin_fd)
{
	DIR		*check;

	check = opendir(head->args[0]);
	if (check)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(head->args[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit_handler(data, stdin_fd, check, 126);
	}
	else if (!data->validpath && access(head->args[0], X_OK | R_OK) == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(head->args[0]);
			exit_handler(data, stdin_fd, check, 126);
		}
		is_builtin(data, head, stdin_fd, NULL);
	}
}

void	wait_for_children(t_shell *data)
{
	t_cmd_table	*head;
	int			status;

	head = *data->cmd_table;
	while (head)
	{
		waitpid(head->pid, &status, 0);
		head = head->next;
	}
	if (WIFEXITED(status))
		data->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit = WTERMSIG(status) + 128;
}

static int	child2(t_cmd_table *head, t_shell *data, int stdin_fd)
{
	head->path = find_path(data, head->args[0]);
	if (data->validpath == MALLOC_ERROR)
		return (-1);
	head->pid = fork();
	if (!head->pid)
	{
		listen(data, CHILD);
		if (set_redirections(data, head) == -1)
			exit (1);
		check_permission(data, head, stdin_fd);
		if (head->path)
			execve(head->path, head->args, data->environment);
		if (!data->exit)
			data->exit = 1;
		exit_handler(data, stdin_fd, NULL, data->exit);
	}
	return (0);
}

/**
 * The function `child_process` creates a child process, redirects input and 
 * output if necessary and executes a command while the parent waits.
 * 
 */
void	child1(t_cmd_table *head, t_shell *data, int stdin_fd)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit (0);
	head->pid = fork();
	if (!head->pid)
	{
		listen(data, CHILD);
		close(pipe_fd[0]);
		if (head->outfile != NO_FD)
		{
			if (dup2(head->outfile, 1) == -1)
				exit(1);
		}	
		else
			dup2(pipe_fd[1], 1);
		heredoc(head, data);
		is_builtin(data, head, stdin_fd, pipe_fd);
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
		head = head->next;
		if (head && head->pipe)
			head = head->next;
	}
	if (child2(head, data, stdin_fd) == -1)
		return (close(stdin_fd), -1);
	dup2(stdin_fd, 0);
	close(stdin_fd);
	wait_for_children(data);
	return (0);
}
