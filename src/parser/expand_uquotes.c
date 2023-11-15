/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_uquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:29:32 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/10 16:09:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function expands any variables in a given sequence by replacing them 
 * with their corresponding values.
 * 
 * @param sequence A pointer to a character array (string) that represents 
 * a sequence of characters.
 * @param data The "data" parameter is of type "t_shell", which is a struct
 * that contains information about the shell environment.
 * 
 * @return a pointer to a character, which is the modified sequence.
 */
char	*expand_uquotes(char *sequence, t_shell *data)
{
	if (*sequence == '$' && (*(sequence + 1) || myisspace(*(sequence + 1))))
	{
		sequence = replace(sequence, data);
		if (!sequence)
			return (NULL);
	}
	return (sequence);
}
