/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_uquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:29:32 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 12:58:43 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function expands any variables in a given sequence by replacing them with their corresponding
 * values.
 * 
 * @param sequence A pointer to a character array (string) that represents a sequence of characters.
 * @param data The "data" parameter is of type "t_shell", which is likely a struct that contains
 * information about the shell environment. It could include variables, settings, and other data
 * related to the shell.
 * 
 * @return a pointer to a character, which is the modified sequence.
 */
char	*expand_uquotes(char *sequence, t_shell *data)
{
	if (*sequence == '$')
	{
		sequence = replace(sequence, data);
		if (!sequence)
			return (NULL);
	}
	return (sequence);
}
