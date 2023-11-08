/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:52:49 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/08 21:58:18 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define EXIT 1789
# define IN_DOUBLE_QUOTES 0x22
# define IN_SINGLE_QUOTES 0x27
# define UNQUOTED 0x00
# define PIPE 0x7c 
# define IN_REDIR 0x3c
# define OUT_REDIR 0x3e
# define APPEND 0x3e3e
# define HEREDOC 0x3c3c
# define SPECIAL_CHAR 999999
# define NO_FD 0

# define SUCCESS 0
# define FAILURE 1
# define NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127
# define CTRL_C 130

#endif