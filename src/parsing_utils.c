/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:47:35 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/21 18:39:44 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	isquote_single(char pos, int *status)
{
	if (pos == '\'' && *status != IN_SINGLE_QUOTES)
		*status = IN_SINGLE_QUOTES;
	else if (pos == '\'' && *status == IN_SINGLE_QUOTES)
		*status = UNQUOTED;
}

void	isquote_double(char pos, int *status)
{
	if (pos == '\"' && *status != IN_DOUBLE_QUOTES)
		*status = IN_DOUBLE_QUOTES;
	else if (pos == '\"' && *status == IN_DOUBLE_QUOTES)
		*status = UNQUOTED;
}

int	isquote(char pos, int *status)
{
	isquote_double(pos, status);
	isquote_single(pos, status);
	if (*status == IN_DOUBLE_QUOTES || *status == IN_SINGLE_QUOTES)
		return (1);
	return (0);
}

int	myisspace(char c)
{
	if (c < 9 || c > 13)
		return (0);
	return (1);
}
