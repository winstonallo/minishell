/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:36:03 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/03 10:40:19 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Get the current working directory's path, trim off everything that comes
before the actual name, and use the new string as a prompt to have cwd
information in prompt*/
int	get_prompt(t_shell *data)
{
	char	*cwd;
	char	*temp;
	size_t	i;

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
			data->prompt = ft_strdup(&cwd[i + 1]);
			free(cwd);
			temp = ft_strjoin("\033[0;36m\033[1m", data->prompt);
			free(data->prompt);
			data->prompt = ft_strjoin(temp, " \x1b[0m🏩 ");
			free(temp);
			return (0);
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
