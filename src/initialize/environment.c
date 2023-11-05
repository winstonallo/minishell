/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:36:03 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/05 15:51:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Get the current working directory's path, trim off everything that comes
before the actual name, and use the new string as a prompt to have cwd
information in prompt*/
int	get_prompt(t_shell *data, size_t i)
{
	char	*cwd;
	char	*temp;

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
			temp = ft_strdup(&cwd[i + 1]);
			if (!temp)
				return (data->exit = FAILURE, -1);
			data->prompt = ft_strjoin(temp, "$ ");
			if (!data->prompt)
				return (data->exit = FAILURE, -1);
			return (free(temp), free(cwd), data->exit = SUCCESS, 0);
		}
	}
	data->prompt = cwd;
	return (data->exit = FAILURE, 0);
}

int	get_environment(t_shell *data, size_t i, size_t j)
{
	char	**t;
	t_env	*new;

	t = data->environment;
	while (t[i])
	{
		j = 0;
		while (t[i][j] != '=' && t[i][j])
		{
			j++;
			if (t[i][j] == '=')
			{
				new = envnew(ft_strndup(t[i], j), &t[i][j + 1],
						ft_strlen(&t[i][j + 1]));
				if (!new)
					return (data->exit = FAILURE, -1);
				envadd_back(data->env_list, new);
			}
		}
		i++;
	}
	return (data->exit = SUCCESS, 0);
}
