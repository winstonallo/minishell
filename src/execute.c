/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:33:12 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/28 13:51:45 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

/*🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧
Here is where we actually execute the commands. A lot of things are missing,
this is just for testing purposes for now. See github issues for more details
on what is left to implement*/
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

void	child_process(t_shell *data)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (!pid && (*data->cmd_table)->outfile != NO_FD)
			if (redirect_output((*data->cmd_table)->outfile) == -1)
				exit (1);
		if (!pid && (*data->cmd_table)->infile != NO_FD)
			if (redirect_input((*data->cmd_table)->infile) == -1)
				exit (1);
		execve(data->command, (*data->cmd_table)->args, data->environment);
		ft_putstr_fd(data->command, 2);
		perror(": failed to execute command");
		wipe(data);
		exit (0);
	}
	waitpid(pid, NULL, 0);
}

int	execute_command(t_shell *data)
{
	data->command = find_path(data, (*data->cmd_table)->args[0]);
	if (!data->command)
		return (-1);
	child_process(data);
	free(data->command);
	return (0);
}
