/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:53:46 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/29 15:04:27 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "lists.h"

typedef struct s_shell
{
	char				*raw_input;
	char				**input_array;
	char				**environment;
	char				*command_path;
	char				**command_args;
	struct s_quotes		**sequences;
	struct s_path		**paths;
	struct s_op			**operators;
	struct s_cmd_table	**cmd_table;
	struct s_cmd_table	*cmd_head;
}	t_shell;

#endif