/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:30:13 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:53:47 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `pwd` prints the current working directory.
 * 
 * @param data The parameter `data` is a pointer to a structure of type `t_shell`.
 * 
 * @return either SUCCESS or FAILURE.
 */
int	pwd(t_shell *data)
{
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return (FAILURE);
	printf("%s\n", data->cwd);
	return (SUCCESS);
}
