/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:39:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/23 04:14:02 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_here_sig(int signal)
{
	if (signal == SIGINT)
		exit(1);
}

static void	do_heredoc(t_cmd_table *head)
{
	char	*line;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_here_sig);
		line = readline("> ");
		if (!strncmp(line, head->heredoc, ft_strlen(head->heredoc) + 1))
			break ;
		write(head->infile, line, ft_strlen(line));
		write(head->infile, "\n", 1);
		free(line);
	}
	free(line);
	close(head->infile);
}
void	heredoc(t_cmd_table *head, t_shell *data)
{
	if (data)
		do_heredoc(head);
	head->infile = open("heredoc", O_RDONLY);
}