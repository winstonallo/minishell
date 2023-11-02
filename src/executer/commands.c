/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:09:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/02 18:14:32 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧
Here we look for the commands that we do not execute using execve (the 7
specified in the subject) and execute them if found, otherwise we pass the 
command line to the executing part*/
int	get_prompt(t_shell *data)
{
	char	*cwd;
	char	*temp;
	size_t	i;

	if (data->prompt)
		free(data->prompt);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	i = ft_strlen(cwd);
	while (cwd[--i])
	{
		if (cwd[i] == '/')
		{
			data->prompt = ft_strdup(&cwd[i + 1]);
			free(cwd);
			temp = ft_strjoin("\033[0;36m\033[1m", data->prompt);
			free(data->prompt);
			data->prompt = ft_strjoin(temp, " \x1b[0m🏩 ");
			free(temp);
			return (0);
		}
	}
	data->prompt = cwd;
	return (0);
}

void	env(t_shell *data)
{
	t_env	*head;

	head = *data->env_list;
	while (head)
	{
		printf("%s=%s\n", head->name, head->line);
		head = head->next;
	}
}

int	find_command(t_shell *data)
{
	if (ft_strncmp((*data->cmd_table)->args[0], "env", 4) == 0)
		return (env(data), 0);
	else if (ft_strncmp((*data->cmd_table)->args[0], "exit", 5) == 0)
		return (EXIT);
	else if (ft_strncmp((*data->cmd_table)->args[0], "export", 6) == 0)
		return (export(data), 0);
	else if (ft_strncmp((*data->cmd_table)->args[0], "cd", 3) == 0)
		return (cd(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "pwd", 4) == 0)
		return (pwd(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "echo", 5) == 0)
		return (echo(data, 0));
	else if (execute_command(data) == 0)
		return (0);
	return (COMMAND_NOT_FOUND);
}
