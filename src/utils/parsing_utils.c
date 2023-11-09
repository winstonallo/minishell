/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:47:35 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 22:05:44 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Check for single quote and set status accordingly based on the previous status
*/
void	issquote(char pos, int *status)
{
	if (pos == '\'' && *status == UNQUOTED)
		*status = IN_SINGLE_QUOTES;
	else if (pos == '\'' && *status == IN_SINGLE_QUOTES)
		*status = UNQUOTED;
}

/*Check for double quotes and set status accordingly based on previous
status*/
void	isdquote(char pos, int *status)
{
	if (pos == '\"' && *status == UNQUOTED)
		*status = IN_DOUBLE_QUOTES;
	else if (pos == '\"' && *status == IN_DOUBLE_QUOTES)
		*status = UNQUOTED;
}

/*Call both isquote functions, set status accordingly and return 1 if 
currently in quotes*/
int	isquote(char pos, int *status)
{
	isdquote(pos, status);
	issquote(pos, status);
	if (*status == IN_DOUBLE_QUOTES || *status == IN_SINGLE_QUOTES)
		return (1);
	else
		*status = UNQUOTED;
	return (0);
}

/*Check for space or alphanumeric characters, needed for argument
expansion*/
int	myisspacealnum(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ' || !ft_isalnum(c))
		return (1);
	return (0);
}

/*Check for spaces*/
int	myisspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}
