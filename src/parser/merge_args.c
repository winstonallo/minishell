/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:57:06 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/20 22:29:27 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	merge_args(t_shell *data)
{
	t_op	**new_list;
	t_op	*new;
	t_op	*head;
	char		*temp;
	
	new_list = malloc(sizeof(t_op));
	if (!new_list)
		return (-1);
	*new_list = NULL;
	head = *data->operators;
	while (head)
	{
		if (head->sequence)
		{
			temp = ft_strdup(head->sequence);
			if (!temp)
				return (-1);
		}
		while (head && head->status != PUT_SPACE_HERE && head->next && head->next->status != PUT_SPACE_HERE)
		{
			temp = ft_strjoin(temp, head->next->sequence);
			if (!temp)
				return (-1);
			head = head->next;
			if (!head || head->status == PUT_SPACE_HERE)
			{
				new = opnew(temp, 0, head->s_char, ft_strlen(temp));
				if (!new)
					return (-1);
				opadd_back(new_list, new);
				break ;
			}
		}
		if (head)
		{
			new = opnew(temp, 0, head->s_char, ft_strlen(temp));
			if (!new)
				return (-1);
			opadd_back(new_list, new);
		}
		if (head)
			head = head->next;
	}
	data->operators = new_list;
	return (0);
}

