/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:30:13 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/03 10:30:30 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(t_shell *data)
{
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return (-1);
	printf("%s\n", data->cwd);
	return (0);
}