/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special_characters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:35:55 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 13:07:20 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function isop checks if a character is a special operator and 
 * updates a variable in a data structure accordingly.
 * 
 * @param s A pointer to a character array (string) that is being checked 
 * for specific characters.
 * @param j The parameter `j` is a pointer to a `size_t` variable. It is used 
 * to keep track of the
 * current position in the string `s`. The value of `j` is 
 * incremented when certain characters are
 * encountered in the string.
 * @param data The parameter `data` is of type `t_shell`, a struct that
 * contains various data related to the shell.
 * 
 * @return 1 if a special character is found and assigned to the 
 * `data->s_char_tmp` variable, and 0 otherwise.
 */
int	isop(char *s, size_t *j, t_shell *data)
{
	if (*s == '|' && !data->s_char_tmp)
		data->s_char_tmp = PIPE;
	else if (*s == '<' && *(s + 1) != '<' && !data->s_char_tmp)
		data->s_char_tmp = IN_REDIR;
	else if (*s == '>' && *(s + 1) != '>' && !data->s_char_tmp)
		data->s_char_tmp = OUT_REDIR;
	else if (*s == '>' && *(s + 1) == '>' && !data->s_char_tmp)
	{
		*j += 1;
		data->s_char_tmp = APPEND;
	}
	else if (*s == '<' && *(s + 1) == '<' && !data->s_char_tmp)
	{
		*j += 1;
		data->s_char_tmp = HEREDOC;
	}
	if (data->s_char_tmp)
		return (1);
	return (0);
}

/**
 * The function adds a new node with a special character to a linked list.
 * 
 * @param seq A pointer to a character array representing a sequence of 
 * characters.
 * @param len The parameter "len" represents the length of the sequence "seq".
 * @param data A pointer to a structure of type t_shell.
 * @param status The "status" parameter is an integer value that represents
 * the status of the node being added.
 * @return an integer value. If the operation is successful, it returns 0. 
 * If there is an error, it returns -1.
 */
int	add_node_special_char(char *seq, size_t len, t_shell *data, int status)
{
	t_op	*new;

	new = opnew(seq, UNQUOTED, status, len);
	if (!new)
		return (-1);
	opadd_back(data->operators, new);
	data->s_char_tmp = 0;
	return (0);
}

/**
 * The function "split_curr_sequence" splits a given sequence into smaller
 * sequences based on certain conditions and adds them as nodes to a structure.
 * 
 * @param seq A pointer to a character array representing a sequence of 
 * characters.
 * @param d The parameter `d` is of type `t_shell*`, which is a pointer to a
 * structure `t_shell`.
 * 
 * @return the value of `d->exit`.
 */
int	split_curr_sequence(char *seq, t_shell *d)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (seq && seq[++i] && seq[j])
	{
		i = j;
		while (!isop(&seq[j], &j, d) && seq[j])
		{
			j++;
			if ((isop(&seq[j], &j, d) || !seq[j]))
			{
				if (add_node_special_char(&seq[i], j - i, d, 0) == -1)
					return (free_opps(d->operators), d->exit);
			}
		}
		if (isop(&seq[j], &j, d))
		{
			if (add_node_special_char(NULL, 0, d, d->s_char_tmp) == -1)
				return (free_opps(d->operators), d->exit);
			j++;
		}
	}
	return (d->exit);
}

/**
 * The function `parse_special_char` parses special characters in a shell
 * command and adds them to the list of operators in the `data` structure.
 * 
 * @param data The parameter `data` is of type `t_shell*`, which is a pointer
 * to a structure `t_shell`.
 * @return the value of `data->exit`.
 */
int	parse_special_char(t_shell *data)
{
	t_quotes	*t;
	t_op		*new;

	t = *data->sequences;
	while (t)
	{
		if (t->status == UNQUOTED)
		{
			if (split_curr_sequence(t->sequence, data) == -1)
				return (data->exit);
		}
		else
		{
			new = opnew(t->sequence, t->status, 0, ft_strlen(t->sequence));
			if (!new)
				return (-1);
			opadd_back(data->operators, new);
		}
		t = t->next;
	}
	return (data->exit);
}
