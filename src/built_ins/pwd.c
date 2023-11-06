/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:30:13 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/06 08:17:14 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(t_shell *data)
{
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return (FAILURE);
	printf("%s\n", data->cwd);
	return (SUCCESS);
}
