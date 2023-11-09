/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:05:19 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 18:34:59 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_pipes(t_shell *data, t_cmd_table *head)
{
	if (pipe(data->pipe_fd) == -1)
		return (perror("pipe"), -1);
	if (head->outfile)
		return (0);
	else
	{
		head->outfile = data->pipe_fd[1];
		if (!head->next->next->infile)
			head->next->next->infile = data->pipe_fd[0];
	}
	return (0);
}
