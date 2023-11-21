/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:57:06 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/21 15:39:04 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_op	*get_next_token(t_op **head)
{
	char	*temp;
	t_op	*new;

	temp = NULL;
	if (*head && (*head)->status == PUT_SPACE_HERE)
		*head = (*head)->next;
	while ((*head) && (*head)->status != PUT_SPACE_HERE)
	{
		if (!temp)
			temp = ft_strdup((*head)->sequence);
		else
			temp = ft_strjoin(temp, (*head)->sequence);
		if (!temp)
			return (NULL);
		if (*head && (*head)->s_char)
		{
			new = opnew(NULL, 0, (*head)->s_char, 0);
			*head = (*head)->next;
			return (new);
		}
		*head = (*head)->next;
		if (!(*head) || (*head)->status == PUT_SPACE_HERE)
			return (opnew(temp, 0, 0, ft_strlen(temp)));
	}
	return (NULL);
}

int	merge_args(t_shell *data)
{
	t_op	**new_list;
	t_op	*new;
	t_op	*head;
	
	new_list = malloc(sizeof(t_op));
	if (!new_list)
		return (-1);
	*new_list = NULL;
	head = *data->operators;
	while (head)
	{
		new = get_next_token(&head);
		if (!new)
			break ;
		opadd_back(new_list, new);
	}
	data->operators = new_list;
	return (0);
}

