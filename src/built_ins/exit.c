/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:49:20 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 13:51:13 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	gtfo(t_shell *data, long status, char *arg)
{
	if (arg && data->allocated)
		free(arg);
	if (status)
		data->exit = status;
	wipe4real(data);
	printf("exit\n");
	exit (data->exit);
}

static void	exit_num_arg(t_shell *data)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd((*data->cmd_table)->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	gtfo(data, 2, NULL);
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
		if (!ft_isdigit(args[1][j]) && args[1][j] != '+' && args[1][j] != '-')
			exit_num_arg(data);
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

static int	num_arg(t_shell *data, char *arg)
{
	int	i;
	int	ret;

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
	ret = ft_atoi(arg);
	return (ret % 255);
}

int	myexit(t_shell *data)
{
	char	*arg;
	int		ret;

	if (!*data->cmd_table || !(*data->cmd_table)->args[1])
		gtfo(data, 0, NULL);
	if ((*data->cmd_table)->next)
		return (0);
	arg = get_arg((*data->cmd_table)->args, data, -1, 0);
	if (!arg && data->validexit)
	{
		printf("exit\n");
		wipe4real(data);
		exit(SUCCESS);
	}
	else if (!arg && !data->validexit)
		return (FAILURE);
	if ((*data->cmd_table)->args[1])
	{
		ret = num_arg(data, arg);
		gtfo(data, ret, arg);
	}
	wipe4real(data);
	printf("exit\n");
	exit(SUCCESS);
}
