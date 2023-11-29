/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:39:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/29 22:42:04 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_heredoc_error(char *eof)
{
	static int	j = 0;
	
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(j++, 2);
	ft_putstr_fd(" delimited by end-of-file(wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n", 2);
}

static void	do_heredoc(t_cmd_table *head, t_shell *data)
{
	char	*line;

	while (1)
	{
		listen(data, HEREDOC);
		head->infile = open(".temp_heredoc", O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (head->infile < 0)
			exit(1);
		line = readline("> ");
		if (!line)
		{
			print_heredoc_error(head->heredoc);
			break ;
		}
		if (!ft_strncmp(line, head->heredoc, ft_strlen(head->heredoc) + 1))
			break ;
		ft_putendl_fd(line, head->infile);
		free(line);
	}
	free(line);
	close(head->infile);
}

void	heredoc(t_cmd_table *head, t_shell *data)
{
	if (data && head->heredoc)
		do_heredoc(head, data);
	head->infile = open("heredoc", O_RDONLY);
}
