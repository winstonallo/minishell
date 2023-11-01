/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_uquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:29:32 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/26 10:22:49 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*This is where we expand unquoted sequences, note that this process is way 
simpler than for the double quotes because the unquoted sequences are already
split into words*/
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
