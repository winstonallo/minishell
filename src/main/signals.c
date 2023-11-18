/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:24:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/18 15:38:50 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	sigint(int signo)
{
	if (signo)
	{
		g_sig = CTRL_C;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	listen(void)
{
	struct sigaction	sig;

	sig.sa_flags = 0;
	sig.sa_handler = sigint;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
}
