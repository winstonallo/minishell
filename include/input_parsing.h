/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:00:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/25 21:47:54 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PARSING_H
# define INPUT_PARSING_H

# include "structs.h"
# include "lists.h"

int			myisspace(char c);
int			myisspacealnum(char c);
int			isquote(char pos, int *status);
int			parse_for_quotes(t_shell *data);
void		free_quoted_sequences(t_quotes **quoted_sequences);
t_quotes	*quotenew(char *content, int status, unsigned long len);
void		opadd_back(t_op **lst, t_op *new_node);
t_op		*opnew(char *content, int status, int op, unsigned long len);
void		quoteadd_back(t_quotes **lst, t_quotes *new_node);
int			parse_special_char(t_shell *data);
char		*expand_dquotes(char *sequence, t_shell *data);
char		*expand_uquotes(char *sequence, t_shell *data);
char		*replace(char *str, t_shell *data);
int			remove_escape(t_shell *data);
int			get_command_table(t_shell *data);

#endif