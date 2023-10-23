/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:53:46 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/23 18:58:16 by abied-ch         ###   ########.fr       */
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
	char				*command;
	char				**command_args;
	struct s_quotes		**sequences;
	struct s_path		**paths;
	struct s_op			**operators;
}	t_shell;

#endif