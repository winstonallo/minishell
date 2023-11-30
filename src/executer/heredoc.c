/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:39:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 05:33:27 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_heredoc_error(char *eof, int j)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(j, 2);
	ft_putstr_fd(" delimited by end-of-file(wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n", 2);
}

static char	*write_to_doc(t_shell *data, char *line, int file)
{
	char	*temp;
	
	temp = expand_heredoc(data, line);
	if (!temp)
		return (NULL);
	ft_putendl_fd(temp, file);
	return (temp);
}

static int	do_heredoc(t_cmd_table *head, t_shell *data)
{
	char		*line;
	static int	j = 0;

	while (++j)
	{
		listen(data, HEREDOC);
		head->infile = open(".temp_heredoc", O_CREAT | O_WRONLY
				| O_APPEND, 0644);
		if (head->infile < 0)
			exit(1);
		line = readline("> ");
		if (g_sig == CTRL_C)
			return (close(head->infile), free(line), 1);
		if (!line)
		{
			print_heredoc_error(head->heredoc, j);
			break ;
		}
		if (!ft_strncmp(line, head->heredoc, ft_strlen(head->heredoc) + 1))
			break ;
		line = write_to_doc(data, line, head->infile);
		if (!line)
			break ;
	}
	return (free(line), close(head->infile), 0);
}

void	heredoc(t_cmd_table *head, t_shell *data)
{
	if (!head->heredoc)
		return ;
	if (data && head->heredoc)
	{
		if (data->exit == COMMAND_NOT_FOUND)
			data->exit = 0;
		if (do_heredoc(head, data))
		{
			data->exit = 130;
			head->infile = HEREDOCINT;
			return ;
		}
	}
	listen(data, NON_INTERACTIVE);
	head->infile = open(".temp_heredoc", O_RDONLY);
}
