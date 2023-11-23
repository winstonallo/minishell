/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:39:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/23 15:12:52 by arthur           ###   ########.fr       */
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
		head->infile = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (!head->infile)
			exit(1);
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
	if (data && head->heredoc)
		do_heredoc(head);
	head->infile = open("heredoc", O_RDONLY);
}
