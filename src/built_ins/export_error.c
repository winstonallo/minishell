/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:32:48 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/08 17:33:17 by sstanfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_issign(char *arg)
{
	if (ft_strchr(arg, '-') != NULL)
		return (1);
	else if (ft_strchr(arg, '*') != NULL)
		return (1);
	else if (ft_strchr(arg, '/') != NULL)
		return (1);
	return (0);
}
int	export_error(char *arg)
{
	if ((ft_strchr(arg, '=') != NULL) && arg[2] == '\0')
		return (ft_putstr_fd(" not a valid identifier", 2), 1);
	else if (ft_strnstr(arg, "-=", ft_strlen(arg)) != 0)
		return (ft_putstr_fd(" not a valid identifier", 2), 1);
	else if (ft_strchr(arg, '=') == NULL)
	//if no '=' in arg[i]
	{
		if (ft_issign(arg) != 0)
			return (ft_putstr_fd(" not a valid identifier", 2), 1);
		if ((ft_isdigit(arg[1])))
			return (ft_putstr_fd(" not a valid identifier", 2), 1);
		return (2);
	}
	return (0);
}