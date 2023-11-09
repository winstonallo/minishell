/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:33:12 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 19:35:51 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

/**
 * The function `child_process` creates a child process, redirects input and 
 * output if necessary and executes a command while the parent waits.
 * 
 */
void	child1(t_cmd_table *head, t_shell *data)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (head->next && head->next->pipe)
			set_pipes(data, head);
		if (!pid && (head->outfile != NO_FD))
			if (redirect_output(data, head->outfile) == -1)
				exit(1);
		if (!pid && head->infile != NO_FD)
			if (redirect_input(data, head->infile) == -1)
				exit(1);
		execve(head->path, head->args, data->environment);
		ft_putstr_fd(data->command_path, 2);
		perror(": failed to execute command");
		wipe(data);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

/**
 * The function executes a command by finding its path, creating a child 
 * process, and freeing the command path.
 */
int	execute_command(t_shell *data)
{
	t_cmd_table	*head;

	head = *data->cmd_table;
	while (head)
	{
		head->path = find_path(data, head->args[0]);
		if (!head->path)
			return (-1);
		child1(head, data);
		free(head->path);
		head = head->next;
		if (head->pipe)
			head = head->next;
		perror("du hund\n");
	}
	return (0);
}
