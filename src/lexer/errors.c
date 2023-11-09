/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:43:39 by arthur            #+#    #+#             */
/*   Updated: 2023/11/09 16:01:43 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int check_quotes(t_shell *data)
{
    int i;
    int status;

    i = -1;
    while (data->raw_input[++i])
        isquote(data->raw_input[i], &status);
    if (status != UNQUOTED)
        return (-1);
    return (0);
}

int lexer(t_shell *data)
{
    if (check_quotes(data) == -1)
        return (ft_putstr_fd("minishell: unclosed quotes\n", 2), -1);
    return (0);
}