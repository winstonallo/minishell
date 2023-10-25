/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_uquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:29:32 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/25 21:47:43 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
