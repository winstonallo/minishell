/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:33:12 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 05:56:02 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <math.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

static void	check_permission(t_shell *data, t_cmd_table *head, int *pipe_fd)
{
	DIR		*check;

	if (!head->args || !head->args[0])
		return ;
	check = opendir(head->args[0]);
	if (check)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(head->args[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		data->exit = 126;
		exit_handler(data, check, head);
	}
	else if (!data->validpath && access(head->args[0], X_OK | R_OK) == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(head->args[0]);
			data->exit = 126;
			exit_handler(data, check, head);
		}
	}
	data->exit = is_builtin(data, head, pipe_fd);
}

static void	wait_for_children(t_shell *data)
{
	t_cmd_table	*head;
	int			status;

	head = *data->cmd_table;
	while (head)
	{
		if (head->pid != NOTACHILD)
			waitpid(head->pid, &status, 0);
		head = head->next;
	}
	if (WIFEXITED(status))
		data->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit = WTERMSIG(status) + 128;
}

static int	child2(t_cmd_table *head, t_shell *data)
{
	if (!head)
		return (-1);
	if (head && head->args && head->args[0])
		head->path = find_path(data, head->args[0]);
	if (data->validpath == MALLOC_ERROR)
		return (-1);
	head->pid = fork();
	if (!head->pid)
	{
		listen(data, CHILD);
		if (set_redirections(data, head) == -1)
		{
			data->exit = 1;
			exit_handler(data, NULL, head);
		}
		checkcmds(head, data, NULL);
		check_permission(data, head, NULL);
		if (head->path && head->infile != HEREDOCINT && head->args
			&& head->args[0])
			execve(head->path, head->args, data->environment);
		if (!data->exit)
			data->exit = 1;
		exit_handler(data, NULL, head);
	}
	return (0);
}

/**
 * The function `child_process` creates a child process, redirects input and 
 * output if necessary and executes a command while the parent waits.
 * 
 */
void	child1(t_cmd_table *head, t_shell *data)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit_handler(data, NULL, head);
	head->pid = fork();
	if (!head->pid)
	{
		listen(data, CHILD);
		checkcmds(head, data, pipe_fd);
		close(pipe_fd[0]);
		heredoc(head, data);
		if (set_redirections(data, head) == -1)
			exit_handler(data, NULL, head);
		else if (dup2(pipe_fd[1], 1) == -1)
			exit_handler(data, NULL, head);
		check_permission(data, head, pipe_fd);
		if (head->path && head->infile != HEREDOCINT && head->args
			&& head->args[0])
			execve(head->path, head->args, data->environment);
		close(pipe_fd[1]);
		exit_handler(data, NULL, head);
	}
	close_pipe_init_fd(pipe_fd);
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

	data->stdin_fd = dup(0);
	i = -1;
	head = *data->cmd_table;
	pipes = count_pipes(data);
	while (++i < pipes)
	{
		head->path = find_path(data, head->args[0]);
		child1(head, data);
		if (head->heredoc)
			unlink(".temp_heredoc");
		head = head->next;
		if (head && head->pipe)
			head = head->next;
	}
	if (child2(head, data) == -1)
		return (close(data->stdin_fd), -1);
	unlink(".temp_heredoc");
	dup2(data->stdin_fd, 0);
	close(data->stdin_fd);
	wait_for_children(data);
	return (0);
}
