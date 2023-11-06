/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:36:03 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/06 10:21:29 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Get the current working directory's path, trim off everything that comes
before the actual name, and use the new string as a prompt to have cwd
information in prompt*/
/* put this back before pushing data->prompt = ft_strjoin(temp, "$ ");*/
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
				return (-1);
			data->prompt = ft_strdup("");
			if (!data->prompt)
				return (-1);
			return (free(temp), free(cwd), 0);
		}
	}
	data->prompt = cwd;
	return (0);
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
					return (-1);
				envadd_back(data->env_list, new);
			}
		}
		i++;
	}
	return (0);
}
