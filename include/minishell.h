/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:59:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/02 15:34:44 by sstanfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "lists.h"
# include "macros.h"
# include "structs.h"

int			main(int argc, char **argv, char **env);

/*Command execution*/
int			execute_command(t_shell *data);
int			redirect_input(int input_fd);
int			redirect_output(int output_fd);
int			export(t_shell *data);

/*Built-Ins*/
int			cd(t_shell *data);
int			pwd(t_shell *data);

/*Initialization*/
int			initialize_lists(t_shell *data);
int			initialize_sequences(t_shell *data);
int			initialize_command_table(t_shell *data);
t_env		*envnew(char *name, char *content, unsigned long len);
void		envadd_back(t_env **lst, t_env *new_node);
int			get_environment(t_shell *data, size_t i, size_t j);
int			get_paths(t_path **paths, t_shell *data);
int			get_prompt(t_shell *data);

/*Parsing*/
int			parse_for_quotes(t_shell *data);
void		free_quoted_sequences(t_quotes **quoted_sequences);
int			parse_special_char(t_shell *data);
char		*expand_dquotes(char *sequence, t_shell *data);
char		*expand_uquotes(char *sequence, t_shell *data);
char		*replace(char *str, t_shell *data);
int			remove_escape(t_shell *data);
int			get_command_table(t_shell *data);

/*Utils*/
int			myisspace(char c);
int			myisspacealnum(char c);
int			isquote(char pos, int *status);

/*List utils,
	need different ones for each list because of different name/content*/
t_quotes	*quotenew(char *content, int status, unsigned long len);
void		opadd_back(t_op **lst, t_op *new_node);
t_op		*opnew(char *content, int status, int op, unsigned long len);
void		quoteadd_back(t_quotes **lst, t_quotes *new_node);
void		cmdadd_back(t_cmd_table **lst, t_cmd_table *new_node);
t_cmd_table	*cmdnew(int outfile, int infile, int pepi);

/*Input reading*/
int			loop(t_shell *data);
int			find_command(t_shell *data);
int			expand_sequences(t_shell *data);

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

#endif