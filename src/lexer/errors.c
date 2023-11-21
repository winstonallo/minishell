/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:43:39 by arthur            #+#    #+#             */
/*   Updated: 2023/11/21 23:13:30 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_syntax_error(int s_char)
{
	if (s_char == IN_REDIR)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (s_char == OUT_REDIR)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (s_char == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (s_char == 0)
		ft_putstr_fd("minishell: syntax error near unexpected token\
			`newline'\n", 2);
}

static int	check_unexpected_token(t_shell *data)
{
	t_op	*head;

	head = *data->operators;
	while (head)
	{
		if (head->s_char && head->next && head->next->s_char)
		{
			data->exit = 2;
			return (print_syntax_error(head->next->s_char), -1);
		}
		else if (head->s_char && !head->next)
		{
			data->exit = 2;
			return (print_syntax_error(0), -1);
		}
		head = head->next;
	}
	return (0);
}

int	lexer(t_shell *data)
{
	if (check_unexpected_token(data) == -1)
		return (-1);
	return (0);
}
