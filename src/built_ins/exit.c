/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:49:20 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/12 18:25:36 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_arg(char **args)
{
	int	j;
	int	sign;

	j = -1;
	while (args[1][++j])
	{
		if (args[1][j] == '+' && sign != 9)
			sign = 3;
		else if (args[1][j] == '-' && sign != 3 && sign != 9)
			sign = 9;
		else
			sign = 0;
	}
	if (!sign && args[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), NULL);
	else if (sign && args[3])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), NULL);
	if (sign)
		return (ft_strjoin(args[1], args[2]));
	else
		return (args[1]);
	return (0);
}

static void	num_arg(t_shell *data, char *arg)
{
	int	i;

	i = -1;
	while ((*data->cmd_table)->args[1][++i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '+' && arg[i] != '-')
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd((*data->cmd_table)->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			data->exit = 2;
			wipe4real(data);
			exit (data->exit);
		}
	}
}

int	myexit(t_shell *data)
{
	char	*arg;

	arg = get_arg((*data->cmd_table)->args);
	if (!arg)
		return (FAILURE);
	if ((*data->cmd_table)->args[1])
	{
		num_arg(data, arg);
		data->exit = ft_atoi(arg) % 256;
		wipe4real(data);
		exit (data->exit);
	}
	wipe4real(data);
	exit(SUCCESS);
}
