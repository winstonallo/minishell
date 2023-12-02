/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:52:49 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/29 23:55:47 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

extern int		g_sig;

# ifndef TEST_MODE
#  define TEST_MODE 0
# endif

# define EXIT 1789
# define IN_DOUBLE_QUOTES 0x22
# define IN_SINGLE_QUOTES 0x27
# define UNQUOTED 0x00
# define PUT_SPACE_HERE 6969
# define PIPE 0x7c 
# define IN_REDIR 1
# define OUT_REDIR 2
# define APPEND 3
# define HEREDOC 4
# define SPECIAL_CHAR 999999
# define NO_FD 0
# define NOTACHILD 123456789
# define HEREDOCINT 1203861

# define INTERACTIVE 19283612
# define CHILD 1273
# define NON_INTERACTIVE 123423408
# define HEREDOCS 129783

# define SUCCESS 0
# define FAILURE 1
# define NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127
# define CTRL_C 130
# define BREAK 404
# define MALLOC_ERROR 1234

# define GREEN		"\e[92;5;118m"
# define RED 		"\e[91m"
# define YELLOW 	"\e[93;5;226m"
# define GRAY		"\e[33;2;37m"
# define RESET 		"\e[0m"
# define CURSIVE 	"\e[33;3m"
# define BOLD 		"\e[1m"

#endif