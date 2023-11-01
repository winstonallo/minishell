/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:52:03 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/31 21:33:21 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Util functions called to redirect output/input, can be used for pipes as well
to save some lines*/
int	redirect_input(int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return (perror("could not redirect input"), -1);
	return (0);
}

int	redirect_output(int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		return (perror("could not redirect output"), -1);
	return (0);
}
