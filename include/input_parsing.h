/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:00:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 21:17:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PARSING_H
# define INPUT_PARSING_H

# include "structs.h"
# include "lists.h"

int			isquote(char pos, int *status);
int			parse_for_quotes(t_shell *data);
void		free_quoted_sequences(t_quotes **quoted_sequences);
t_quotes	*quotenew(char *content, int status, unsigned long len);
void		quoteadd_back(t_quotes **lst, t_quotes *new_node);

#endif