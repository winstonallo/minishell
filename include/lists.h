/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:54:18 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/30 09:29:16 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include <sys/types.h>

typedef struct s_dox
{
	char			*name;
	struct s_dox	*next;
}	t_dox;

typedef struct s_env
{
	char			*name;
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_path
{
	char				*path;
	struct s_path		*next;
}	t_path;

typedef struct s_quotes
{
	char				*sequence;
	int					status;
	struct s_quotes		*next;
}	t_quotes;

typedef struct s_op
{
	char				*sequence;
	int					s_char;
	int					status;
	struct s_op			*next;
}	t_op;

typedef struct s_cmd_table
{
	char				**args;
	char				*path;
	int					outfile;
	int					infile;
	int					isoutredir;
	int					isinredir;
	int					pipe;
	pid_t				pid;
	char				*heredoc;
	struct s_cmd_table	*next;
}	t_cmd_table;

#endif