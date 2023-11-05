/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:52:03 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/05 16:21:36 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Util functions called to redirect output/input, can be used for pipes as well
to save some lines*/
int	redirect_input(t_shell *data, int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return (perror("output redirection failed"), data->exit = FAILURE);
	return (data->exit = SUCCESS);
}

int	redirect_output(t_shell *data, int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		return (perror("output redirection failed"), data->exit = FAILURE);
	return (data->exit = SUCCESS);
}
