/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:59:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 10:52:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "lists.h"
# include "macros.h"
# include "structs.h"
# include <stddef.h>
# include <errno.h>	
# include <dirent.h>
# include <signal.h>

int			main(int argc, char **argv, char **env);
void		sigint(int signo);
void		listen(t_shell *data, int sig_mode);
int			loop_test(t_shell *data, char *input);

/*Command execution*/
int			count_pipes(t_shell *data);
char		*find_path(t_shell *data, char *command);
int			execute_command(t_shell *data);
int			checkcmd(t_shell *data);
int			is_builtin(t_shell *data, t_cmd_table *head, int *pipe_fd);
void		exit_handler(t_shell *data, DIR *check, t_cmd_table *head);
void		close_pipe_init_fd(int *pipe_fd, t_cmd_table *head);
int			set_redirections(t_shell *data, t_cmd_table *head);
int			set_pipes(t_shell *data, t_cmd_table *head);
int			is_unpipeable(char *cmd);
void		checkcmds(t_cmd_table *head, t_shell *data, int *pipe_fd);
void		heredoc(t_cmd_table *head, t_shell *data, int id);
char		*expand_heredoc(t_shell *data, char *line, size_t i, size_t pos);
char		*get_unexpanded_value(char *str, t_shell *data);

/* ******************************************************************** */
/*								BUILT INS								*/
/* **********************************************************************/

//built_ins.c
int			update_pwd(t_shell *data);
int			cd(t_shell *data, int i);
int			pwd(t_shell *data);
int			echo(t_cmd_table *head, int newline);
int			export(t_shell *data);
int			myexit(t_shell *data);
void		unset(t_shell *data);
int			env(t_shell *data);

//export.c
//export_utils.c
int			update_env_list(t_shell *data);
//export_error.c
int			export_error(char *arg, int argname);

	/* ******************************************************************** */
	/*								INITIALIZATION							*/
	/* **********************************************************************/
	//
int			initialize_lists(t_shell *data);
int			initialize_sequences(t_shell *data);
int			export_env(t_shell *data);
int			envsize(t_env **list);
int			initialize_command_table(t_shell *data);
//
/* ******************************************************************** */
/*								UTILS									*/
/* **********************************************************************/
//
int			get_environment(t_shell *data, size_t i, size_t j);
int			get_paths(t_shell *data);
int			get_prompt(t_shell *data, size_t i);

/*Parsing*/
int			tokenize(t_shell *data);
void		free_quoted_sequences(t_quotes **quoted_sequences);
int			parse_special_char(t_shell *data);
int			expand_dquotes(t_quotes *node, t_shell *data, size_t i,
				size_t pos);
char		**fill_array(size_t *size, char *seq, size_t *pos, t_shell *data);
size_t		count_words(char *seq);
char		*expand_exitcode(char *str, t_shell *data, size_t i);
int			merge_args(t_shell *data);
char		*replace(char *str, t_shell *data);
int			remove_escape(t_shell *data);
int			get_command_table(t_shell *data);
int			uquote(char *unquoted_sequence, t_shell *data);
int			squotes(char *quoted_sequence, t_shell *data);
int			dquotes(char *quoted_sequence, t_shell *data);
char		**get_env_array(t_shell *data);

/*Utils*/
int			myisspace(char c);
int			myisspacealnum(char c);
int			isquote(char pos, int *status);
int			lexer(t_shell *data);
int			check_quotes(t_shell *data);
int			init_vars(t_shell *data, size_t words);
int			open_infile(char *path);

/* ******************************************************************** */
/*								LIST UTILS								*/
/* **********************************************************************/
//
//Quote parsing
//
t_quotes	*quotenew(char *content, int status, unsigned long len);
void		opadd_back(t_op **lst, t_op *new_node);
//
int			doxadd_back(t_dox **lst, t_dox *new_node);
t_dox		*doxnew(char *content);
void		free_dox(t_dox **stack_a);

//Special operator parsing
//
t_op		*opnew(char *content, int status, int op, unsigned long len);
int			quoteadd_back(t_quotes **lst, t_quotes *new_node);
//
//Command table
//
t_cmd_table	*cmdnew(int outfile, int infile, int pepi, char *eof);
void		cmdadd_back(t_cmd_table **lst, t_cmd_table *new_node);
//
//Executable paths list
//
t_path		*pathnew(char *content);
int			update_paths(t_shell *data, char *line);
void		pathadd_back(t_path **lst, t_path *new_node);
//
//Environment list
//
t_env		*envnew(char *name, char *content, unsigned long len);
void		envadd_back(t_env **lst, t_env *new_node);

/*Input reading*/
int			loop(t_shell *data);
int			find_command(t_shell *data, t_cmd_table *head);
int			expand(t_shell *data);

/*Testing utils*/
void		print_quote_list(t_quotes **sequences);
void		print_op_list(t_op **opps);
void		print_cmd_tables(t_cmd_table **cmd_tables);

/*Memory*/
void		free_paths(t_path **stack_a);
int			wipe(t_shell *data);
void		wipe4real(t_shell *data);
void		free_array(char **arr);
void		free_opps(t_op **operators);
void		free_sequences(t_quotes **sequences);
void		free_array_arrsize(char **arr, int arr_size);
void		free_environment(t_env **env);
void		free_env_lists(t_shell *data);
void		free_cmd_tables(t_cmd_table **cmd_tables);

#endif