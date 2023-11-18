/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:59:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/18 20:20:19 by abied-ch         ###   ########.fr       */
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
void		listen(void);

/*Command execution*/
int			count_pipes(t_shell *data);
char		*find_path(t_shell *data, char *command);
int			execute_command(t_shell *data);
int			checkcmd(t_shell *data);
int			is_builtin(t_shell *data, char *path, int stdin_fd, int *pipe_fd);
int			set_redirections(t_shell *data, t_cmd_table *head);
int			set_pipes(t_shell *data, t_cmd_table *head);
int			merge_args(t_cmd_table *cmd_table);


/* ******************************************************************** */
/*								BUILT INS								*/
/* **********************************************************************/

//built_ins.c
int			cd(t_shell *data);
int			pwd(t_shell *data);
int			echo(t_shell *data, int newline);
int			export(t_shell *data);
int			myexit(t_shell *data);

//export.c
int			env(t_shell *data);
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
int			initialize_command_table(t_shell *data);
//
/* ******************************************************************** */
/*								UTILS									*/
/* **********************************************************************/
//
int			get_environment(t_shell *data, size_t i, size_t j);
int			get_paths(t_path **paths, t_shell *data);
int			get_prompt(t_shell *data, size_t i);

/*Parsing*/
int			parse_for_quotes(t_shell *data);
void		free_quoted_sequences(t_quotes **quoted_sequences);
int			parse_special_char(t_shell *data);
int			expand_dquotes(t_quotes *node, t_shell *data, size_t i,
				size_t pos);
char		**fill_array(size_t *size, char *seq, size_t *pos, t_shell *data);
size_t		count_words(char *seq);
char		*expand_exitcode(char *str, t_shell *data, size_t i);

char		*replace(char *str, t_shell *data);
int			remove_escape(t_shell *data);
int			get_command_table(t_shell *data);

/*Utils*/
int			myisspace(char c);
int			myisspacealnum(char c);
int			isquote(char pos, int *status);
int			lexer(t_shell *data);

/* ******************************************************************** */
/*								LIST UTILS								*/
/* **********************************************************************/
//
//Quote parsing
//
t_quotes	*quotenew(char *content, int status, unsigned long len);
void		opadd_back(t_op **lst, t_op *new_node);
//
//Special operator parsing
//
t_op		*opnew(char *content, int status, int op, unsigned long len);
void		quoteadd_back(t_quotes **lst, t_quotes *new_node);
//
//Command table
//
t_cmd_table	*cmdnew(int outfile, int infile, int pepi);
void		cmdadd_back(t_cmd_table **lst, t_cmd_table *new_node);
//
//Executable paths list
//
t_path		*pathnew(char *content);
void		pathadd_back(t_path **lst, t_path *new_node);
//
//Environment list
//
t_env		*envnew(char *name, char *content, unsigned long len);
void		envadd_back(t_env **lst, t_env *new_node);

/*Input reading*/
int			loop(t_shell *data);
int			find_command(t_shell *data);
int			expand(t_shell *data);

/*Testing utils*/
void		print_quote_list(t_quotes **sequences);
void		print_op_list(t_op **opps);
void		print_cmd_tables(t_cmd_table **cmd_tables);

/*Memory*/
void		free_paths(t_path **stack_a);
void		wipe(t_shell *data);
void		wipe4real(t_shell *data);
void		free_array(char **arr);
void		free_opps(t_op **operators);
void		free_sequences(t_quotes **sequences);
void		free_array_arrsize(char **arr, int arr_size);
void		free_environment(t_env **env);
void		free_cmd_tables(t_cmd_table **cmd_tables);

#endif