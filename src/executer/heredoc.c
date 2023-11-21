/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:39:11 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/21 23:49:03 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"

// static void	ft_here_sig(int signal)
// {
// 	if (signal == SIGINT)
// 		exit(1);
// }

// static void	ft_child_sig(int signal)
// {
// 	if (signal == SIGINT)
// 		printf("\n");
// }

// void	heredoc(char *eof)
// {
// 	int		i;
// 	int		fd;
// 	char	*line;

// 	fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
// 	while (1)
// 	{
// 		signal(SIGQUIT, SIG_IGN);
// 		signal(SIGINT, &ft_here_sig);
// 		line = readline(">");
// 		i = strncmp(line, eof, ft_strlen(eof) + 1);
// 		if (i == 0)
// 			break ;
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	free(line);
// 	close(fd);
// 	exit(0);
// }

// static int	ft_exec_heredoc(t_redir *rec)
// {
// 	int		pid;	

// 	pid = fork();
// 	if (pid == 0)
// 		ft_here(rec->file);
// 	waitpid(pid, data->exit, 0);
// 	if (WIFEXITED(g_exit_status))
// 		g_exit_status = WEXITSTATUS(g_exit_status);
// 	return (g_exit_status);
// }

// int	ft_heredoc(t_shell *data)
// {
// 	t_cmd	*cmd;
// 	t_list	*red;
// 	t_redir	*rec;

// 	signal(SIGQUIT, &ft_child_sig);
// 	signal(SIGINT, &ft_child_sig);
// 	while (cmds)
// 	{
// 		cmd = cmds->content;
// 		red = cmd->redir;
// 		while (red != NULL)
// 		{
// 			rec = red->content;
// 			if (rec->type == 'H')
// 			{
// 				if (ft_exec_heredoc(rec) == 1)
// 					return (1);
// 			}
// 			red = red->next;
// 		}
// 		cmds = cmds->next;
// 	}
// 	return (0);
// }
