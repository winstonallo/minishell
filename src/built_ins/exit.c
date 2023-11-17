/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:49:20 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/17 14:53:50 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	gtfo(t_shell *data, int status, char *arg)
{
	if (arg && data->allocated)
		free(arg);
	data->exit = status;
	wipe4real(data);
	// printf("exit\n");
	exit (data->exit);
}

static char	*get_arg(char **args, t_shell *data, int j, int sign)
{
	if (!args[1])
		return (NULL);
	while (args[1][++j])
	{
		if (args[1][j] == '+' && sign != 9)
			sign = 3;
		else if (args[1][j] == '-' && !sign)
			sign = 9;
	}
	if (!sign && args[2])
	{
		data->validexit = 0;
		data->exit = 1;
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), NULL);
	}
	else if (sign && args[2])
	{
		data->allocated = 1;
		return (ft_strjoin(args[1], args[2]));
	}
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
			gtfo(data, 2, arg);
		}
	}
}

int	myexit(t_shell *data)
{
	char	*arg;

	if (!*data->cmd_table)
		gtfo(data, 0, NULL);
	arg = get_arg((*data->cmd_table)->args, data, -1, 0);
	if (!arg && data->validexit)
	{
		//printf("exit\n");
		wipe4real(data);
		exit(SUCCESS);
	}
	else if (!arg && !data->validexit)
		return (FAILURE);
	if ((*data->cmd_table)->args[1])
	{
		num_arg(data, arg);
		gtfo(data, ft_atoi(arg) % 256, arg);
	}
	wipe4real(data);
	//printf("exit\n");
	exit(SUCCESS);
}
