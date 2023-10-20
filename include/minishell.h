/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:59:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 13:02:55 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "macros.h"
# include "structs.h"
# include "lists.h"
# include "memory_management.h"
# include "input_parsing.h"
# include "input_reading.h"
# include "paths.h"
# include "../libft/include/libft.h"

int		main(int argc, char **argv, char **env);

#endif