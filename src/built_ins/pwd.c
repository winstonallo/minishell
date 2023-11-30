/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:30:13 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 02:51:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `pwd` prints the current working directory.
 * 
 * @return either SUCCESS or FAILURE.
 */
int	pwd(t_shell *data)
{
	freeze(data->cwd);
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		exit(FAILURE);
	printf("%s\n", data->cwd);
	wipe4real(data);
	exit(SUCCESS);
}
