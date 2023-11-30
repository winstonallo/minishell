/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:39:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 09:00:00 by abied-ch         ###   ########.fr       */
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

static void	write_to_doc(t_shell *data, char *line, int file)
{
	char	*temp;

	temp = expand_heredoc(data, line, -1, 0);
	if (!temp)
		return ;
	ft_putendl_fd(temp, file);
	free(temp);
}

static int	do_heredoc(t_cmd_table *head, t_shell *data, char *name)
{
	char		*line;
	static int	j = 0;

	head->infile = open(name, O_CREAT | O_WRONLY
			| O_APPEND, 0644);
	while (++j)
	{
		if (head->infile < 0)
			exit(1);
		listen(data, HEREDOC);
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
		write_to_doc(data, line, head->infile);
	}
	return (free(line), close(head->infile), 0);
}

static char	*get_heredoc_name(int id)
{
	char	*name;
	char	*str_id;

	name = ".temp_heredoc";
	str_id = ft_itoa(id);
	if (!str_id)
		return (NULL);
	name = ft_strjoin(name, str_id);
	if (!name)
		return (free(str_id), NULL);
	return (free(str_id), name);
}

void	heredoc(t_cmd_table *head, t_shell *data, int id)
{
	char	*name;

	if (!head->heredoc)
		return ;
	name = get_heredoc_name(id);
	if (!name)
		return ;
	if (doxadd_back(data->dox, doxnew(name)) == -1)
		return ;
	if (data && head->heredoc)
	{
		if (data->exit == COMMAND_NOT_FOUND)
			data->exit = 0;
		if (do_heredoc(head, data, name))
		{
			data->exit = 130;
			head->infile = HEREDOCINT;
			return ;
		}
	}
	listen(data, NON_INTERACTIVE);
	head->infile = open(name, O_RDONLY);
}
