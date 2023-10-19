/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:59:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/19 17:08:16 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"

# define EXIT 1789
# define COMMAND_NOT_FOUND 404 

typedef struct s_shell
{
	char	*raw_input;
	char	**input_array;
	char	**environment;
}	t_shell;

int		main(int argc, char **argv, char **env);
void	read_input(t_shell *data);

#endif