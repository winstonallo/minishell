/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:47:35 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 13:08:54 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	isquote_single(char pos, int *status)
{
	if (pos == '\'' && *status != IN_SINGLE_QUOTES)
		*status = IN_SINGLE_QUOTES;
	else if (pos == '\'' && *status == IN_SINGLE_QUOTES)
		*status = 0;
}

void	isquote_double(char pos, int *status)
{
	if (pos == '\"' && *status != IN_DOUBLE_QUOTES)
		*status = IN_DOUBLE_QUOTES;
	else if (pos == '\"' && *status == IN_DOUBLE_QUOTES)
		*status = 0;
}

void	isquote(char pos, int *insq, int *indq)
{
	isquote_double(pos, indq);
	isquote_single(pos, insq);
}
