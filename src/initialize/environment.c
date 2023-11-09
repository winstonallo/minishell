/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:36:03 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:56:16 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function `get_prompt` retrieves the current working directory and sets it as the prompt for a
 * shell, using the last directory name as the prompt.
 * 
 * @param data A pointer to a struct of type t_shell.
 * @param i The parameter `i` is used as a counter in the function. It is initially passed as an
 * argument to the function, but its value is not used or modified within the function.
 * 
 * @return an integer value. If the function is successful, it returns 0. If there is an error, it
 * returns -1.
 */
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

/**
 * The function `get_environment` parses an array of strings representing environment variables and
 * adds them to a linked list.
 * 
 * @param data A pointer to a structure of type t_shell, which likely contains information about the
 * shell environment.
 * @param i The parameter `i` is used as an index to iterate through the array `t`, which represents
 * the environment variables.
 * @param j The parameter `j` is used as an index to iterate through the characters of the string
 * `t[i]`. It is initialized to 0 before the inner while loop starts, and it is incremented until it
 * reaches the end of the string or encounters the character '='.
 * 
 * @return an integer value. If the function executes successfully, it will return 0. If there is an
 * error, it will return -1.
 */
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
