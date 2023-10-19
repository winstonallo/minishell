/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/19 16:27:41 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_line(t_shell *data)
{
	int	i;

	i = -1;
	if (ft_strncmp(data->raw_input, "env", 4) == 0)
	{
		while (data->environment[++i])
			ft_printf("%s\n", data->environment[i]);
	}
}

void	read_input(t_shell *data)
{
	while (1)
	{
		data->raw_input = readline("$");
		parse_line(data);
		if (ft_strncmp(data->raw_input, "exit", 5) == 0)
			return (free(data->raw_input));
		free(data->raw_input);
	}
}