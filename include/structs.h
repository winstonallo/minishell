/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:53:46 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/29 16:58:11 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "lists.h"
# include <stddef.h>

typedef struct s_token
{
	int					st;
	size_t				i;
	size_t				j;
	size_t				k;
	size_t				words;
	char				**tokens;
}	t_token;

typedef struct s_shell
{
	char				*raw_input;
	char				*temp;
	char				**input_array;
	char				**environment;
	char				*command_path;
	char				**command_args;
	char				*prompt;
	char				*cwd;
	int					stdin_fd;
	int					validexit;
	int					allocated;
	int					exit;
	int					s_char_tmp;
	int					validpath;
	int					sig_mode;
	int					pipe_fd[2];
	struct s_quotes		**sequences;
	struct s_path		**paths;
	struct s_op			**operators;
	struct s_cmd_table	**cmd_table;
	struct s_cmd_table	*cmd_head;
	struct s_env		**env_list;
	struct s_token		tok;
}	t_shell;

#endif