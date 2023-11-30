/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomassshit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:00:57 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 12:13:27 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_unpipeable(char *cmd)
{
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	return (0);
}

void	checkcmds(t_cmd_table *head, t_shell *data, int *pipe_fd)
{
	if (!head->args || !head->args[0])
		return ;
	if (is_unpipeable(head->args[0]))
	{
		data->exit = 0;
		if (pipe_fd)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		return ;
	}
}
