/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:24:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/29 22:46:47 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

volatile sig_atomic_t	g_sig = 0;

void	sigint(int signo)
{
	if (signo == SIGINT)
	{
		g_sig = CTRL_C;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	heredox(int status)
{
	if (status == SIGINT)
	{
		g_sig = CTRL_C;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	listen(t_shell *data, int sig_mode)
{
	if (!data)
		return ;
	if (sig_mode == INTERACTIVE)
	{
		signal(SIGINT, &sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_mode == NON_INTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_mode == HEREDOC)
	{
		signal(SIGINT, &heredox);
		signal(SIGQUIT, SIG_IGN);
	}
}
