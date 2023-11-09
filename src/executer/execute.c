/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:33:12 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:55:17 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function "find_path" searches for the executable file specified by the "command" parameter in
 * the directories listed in the "data->paths" linked list, and returns the full path of the executable
 * if found.
 * 
 * @param data A pointer to a structure of type t_shell, which likely contains information about the
 * shell environment.
 * @param command The `command` parameter is a string that represents the name of the command that we
 * are trying to find the path for.
 * 
 * @return The function `find_path` returns a `char*` which represents the path of the executable file
 * if it is found, or `NULL` if it is not found.
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
 * The function `child_process` creates a child process, redirects input and output if necessary,
 * executes a command while the parent waits.
 * 
 * @param data A pointer to a structure `t_shell` which contains various information related to the
 * shell.
 */
void	child_process(t_shell *data)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (!pid && (*data->cmd_table)->outfile != NO_FD)
			if (redirect_output(data, (*data->cmd_table)->outfile) == -1)
				exit(1);
		if (!pid && (*data->cmd_table)->infile != NO_FD)
			if (redirect_input(data, (*data->cmd_table)->infile) == -1)
				exit(1);
		execve(data->command_path, (*data->cmd_table)->args, data->environment);
		ft_putstr_fd(data->command_path, 2);
		perror(": failed to execute command");
		wipe(data);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

/**
 * The function executes a command by finding its path, creating a child process, and freeing the
 * command path.
 * 
 * @param data A pointer to a structure of type t_shell, which contains information about the shell and
 * the current command being executed.
 * 
 * @return an integer value. If the command table is not empty, it will execute the child process and
 * return 0. If the command table is empty or if the command path is not found, it will return -1.
 */
int	execute_command(t_shell *data)
{
	if (*data->cmd_table)
	{
		data->command_path = find_path(data, (*data->cmd_table)->args[0]);
		if (!data->command_path)
			return (-1);
		child_process(data);
		free(data->command_path);
	}
	return (0);
}
