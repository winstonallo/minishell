/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:22:46 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/02 16:28:30 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export(t_shell *data)
{
	if (ft_strncmp((*data->cmd_table)->args[1], "=", 1) == 0)
		return (-1);
	else if (update_env_list(data) != 0)
		return (-1);
	return (0);
}

int	cd(t_shell *data)
{
	if (chdir((*data->cmd_table)->args[1]) == -1)
	{
		perror("minishell: cd");
		return (-1);
	}
	get_prompt(data);
	return (0);
}

int	pwd(t_shell *data)
{
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return (-1);
	printf("%s\n", data->cwd);
	return (0);
}
