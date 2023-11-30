/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:11:38 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/29 22:14:21 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_tokens_to_list(t_quotes **list, t_shell *data)
{
	t_quotes	*head;

	head = *list;
	while (head)
	{
		if (head->sequence[0] && head->sequence[0] == '"')
			dquotes(head->sequence + 1, data);
		else if (head->sequence[0] == '\'')
			squotes(head->sequence + 1, data);
		else
			uquote(head->sequence, data);
		if (head->next && (head->next->sequence[0] == ' '
				|| head->sequence[ft_strlen(head->sequence) - 1] == ' '
				|| head->sequence[0] == ' '))
		{
			if (quoteadd_back(data->sequences,
					quotenew(NULL, PUT_SPACE_HERE, 0)) == -1)
				return (-1);
		}
		head = head->next;
	}
	return (0);
}

static int	init_token_vars(t_shell *data)
{
	data->tok.pars_temp_list = malloc(sizeof(t_quotes **));
	if (!data->tok.pars_temp_list)
		return (-1);
	*data->tok.pars_temp_list = NULL;
	return (0);
}

t_quotes	**get_token_list(t_shell *data, size_t i, size_t pos, int qu_stat)
{
	t_quotes	*new;

	if (init_token_vars(data) == -1)
		return (NULL);
	isquote(data->raw_input[0], &qu_stat);
	while (data->raw_input[++i])
	{
		data->tok.prev_st = qu_stat;
		isquote(data->raw_input[i], &qu_stat);
		if (qu_stat != data->tok.prev_st || !data->raw_input[i + 1])
		{
			if (!data->raw_input[i + 1] || (data->tok.prev_st && !qu_stat))
				i++;
			new = quotenew(&data->raw_input[pos], 0, i - pos);
			if (!new)
				return (NULL);
			quoteadd_back(data->tok.pars_temp_list, new);
			while (pos < i - 1)
				isquote(data->raw_input[pos++], &qu_stat);
			pos++;
		}
		if (!data->raw_input[i])
			break ;
	}
	return (data->tok.pars_temp_list);
}

int	tokenize(t_shell *data)
{
	t_quotes	**temp_list;

	if (check_quotes(data) == -1)
		return (-1);
	temp_list = get_token_list(data, -1, 0, 0);
	add_tokens_to_list(temp_list, data);
	free_sequences(temp_list);
	return (0);
}
