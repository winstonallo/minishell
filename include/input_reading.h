/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reading.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:58:28 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 21:24:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_READING_H
# define INPUT_READING_H

# include "structs.h"

int			read_input(t_shell *data);
int			find_command(char *command, t_shell *data);
void		expand_sequences(t_shell *data);
void		cmdadd_back(t_cmd_table **lst, t_cmd_table *new_node);
t_cmd_table	*cmdnew(int outfile, int infile, int pepi);

#endif