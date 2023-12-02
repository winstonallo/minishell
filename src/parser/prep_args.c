/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:27:48 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/20 20:57:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"

// static int	make_it_pretty(t_cmd_table *head, char *arg)
// {
// 	char	**new;

// 	new = malloc(3 * sizeof(char *));
// 	if (!new)
// 		return (-1);
// 	new[0] = ft_strdup(head->args[0]);
// 	if (!new[0])
// 		return (free(new), -1);
// 	new[1] = ft_strdup(arg);
// 	if (!new[1])
// 		return (free(new[0]), free(new), -1);
// 	new[2] = NULL;
// 	free_array(head->args);
// 	head->args = new;
// 	free(arg);
// 	return (0);
// }

// int	merge_args(t_cmd_table *cmd_table, int i)
// {
// 	t_cmd_table	*head;
// 	char		*temp;

// 	head = cmd_table;
// 	temp = NULL;
// 	if (!ft_strnstr(head->args[0], "echo", ft_strlen(head->args[0])))
// 		return (1);
// 	if (head->args)
// 	{
// 		while (head->args[++i])
// 		{
// 			temp = ft_strjoin(temp, head->args[i]);
// 			if (!temp)
// 				return (-1);
// 			if (head->args[i][0] && head->args[i + 1] && head->args[i + 1][0])
// 			{
// 				temp = ft_strjoin(temp, " ");
// 				if (!temp)
// 					return (-1);
// 			}
// 		}
// 		make_it_pretty(head, temp);
// 	}
// 	return (0);
// }
