/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstanfel <sstanfel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:11:38 by abied-ch          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/30 01:26:23 by sstanfel         ###   ########.fr       */
=======
/*   Updated: 2023/11/29 16:32:16 by abied-ch         ###   ########.fr       */
>>>>>>> 5adef0d8bc1aaa7af68246a2dfa7d918219fa363
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stddef.h>

//baustelle nix ganz funktionieren
// void	skip_whitespaces(t_shell *data, size_t *j, int *quote_status)
// {
// 	int	prev_status;

// 	prev_status = 0;
// 	while (data->raw_input[*j] && myisspace(data->raw_input[*j]))
// 	{
// 		if (*j > 0)
// 			isquote(data->raw_input[*j - 1], &prev_status);
// 		else
// 			prev_status = *quote_status;
// 		isquote(data->raw_input[*j], quote_status);
// 		(*j)++;
// 	}
// }

// /**The function `fill_token_array` takes a shell structure and the number 
// of words as input, and fills
//  * an array with tokens from the raw input string.
//  * 
//  * @param d The parameter `d` is of type `t_shell*`, which is a pointer 
//  	to a structure of type
//  * `t_shell`.
//  * @param words The parameter "words" represents the number of words in the 
//  	input string.
//  * 
//  * @return a pointer to a character array (char **) called "tokens".
//  */
// static char	**fill_token_array(t_shell *d, size_t words)
// {
// 	if (init_vars(d, words) == -1)
// 		return (NULL);
// 	while (++d->tok.i < words)
// 	{
// 		d->tok.k = d->tok.j;
// 		while (d->tok.j < ft_strlen(d->raw_input) - 1)
// 		{
// 			isquote(d->raw_input[d->tok.j], &d->tok.st);
// 			if ((d->tok.st == UNQUOTED && myisspace(d->raw_input[d->tok.j]))
// 				|| !d->raw_input[d->tok.j + 1])
// 			{
// 				d->tok.j++;
// 				if (!d->raw_input[d->tok.j])
// 					d->tok.j++;
// 				d->tok.tokens[d->tok.i] = ft_strndup(&d->raw_input[d->tok.k],
// 						d->tok.j - d->tok.k - 1);
// 				if (!d->tok.tokens[d->tok.i])
// 					return (free_array(d->tok.tokens), NULL);
// 				if (d->raw_input[d->tok.j])
// 					skip_whitespaces(d, &d->tok.j, &d->tok.st);
// 				break ;
// 			}
// 			d->tok.j++;
// 		}
// 	}
// 	d->tok.tokens[d->tok.i] = NULL;
// 	return (d->tok.tokens);
// }

// char	**get_token_array(t_shell *data, size_t i)
// {
// 	int		quote_status;
// 	int		prev_status;
// 	size_t	words;
// 	char	**token_array;

// 	words = 0;
// 	quote_status = 0;
// 	while (data->raw_input[++i])
// 	{
// 		prev_status = quote_status;
// 		isquote(data->raw_input[i], &quote_status);
// 		if ((quote_status == UNQUOTED || prev_status != quote_status)
// 			&& (myisspace(data->raw_input[i]) || !data->raw_input[i + 1]))
// 			words++;
// 	}
// 	token_array = NULL;
// 	printf("word count: %zu\n", words);
// 	token_array = fill_token_array(data, words);
// 	if (!token_array)
// 		return (NULL);
// 	return (token_array);
// }



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
<<<<<<< HEAD
			prev_status = *quote_status;
		isquote(data->raw_input[*j], quote_status);
		if ((*quote_status == UNQUOTED)
			&& myisspace(data->raw_input[*j])
			&& words)
			*words += 1;
		*j += 1;
	}
}

/**The function `fill_token_array` takes a shell structure and the number 
of words as input, and fills
 * an array with tokens from the raw input string.
 * 
 * @param d The parameter `d` is of type `t_shell*`, which is a pointer 
 	to a structure of type
 * `t_shell`.
 * @param words The parameter "words" represents the number of words in the 
 	input string.
 * 
 * @return a pointer to a character array (char **) called "tokens".
 */
static char	**fill_token_array(t_shell *d, size_t words)
{
	if (init_vars(d, words) == -1)
		return (NULL);
	while (++d->tok.i < words)
	{
		d->tok.k = d->tok.j;
		while (d->tok.j < ft_strlen(d->raw_input))
		{
			isquote(d->raw_input[d->tok.j], &d->tok.st);
			if ((d->tok.st == UNQUOTED && myisspace(d->raw_input[d->tok.j]))
				|| !d->raw_input[d->tok.j + 1])
			{
				d->tok.j++;
				if (!d->raw_input[d->tok.j])
					d->tok.j++;
				d->tok.tokens[d->tok.i] = ft_strndup(&d->raw_input[d->tok.k],
						d->tok.j - d->tok.k - 1);
				if (!d->tok.tokens[d->tok.i])
					return (free_array(d->tok.tokens), NULL);
				break ;
			}
			d->tok.j++;
		}
	}
	d->tok.tokens[d->tok.i] = NULL;
	return (d->tok.tokens);
}

char	**get_token_array(t_shell *data, size_t i)
{
	int		quote_status;
	int		prev_status;
	size_t	words;
	char	**token_array;

	words = 0;
	quote_status = 0;
	while (data->raw_input[++i])
	{
		prev_status = quote_status;
		isquote(data->raw_input[i], &quote_status);
		if ((quote_status == UNQUOTED || prev_status != quote_status)
			&& (myisspace(data->raw_input[i]) || !data->raw_input[i + 1]))
			words++;
	}
	token_array = NULL;
	token_array = fill_token_array(data, words);
	if (!token_array)
		return (NULL);
	return (token_array);
}

int	add_tokens_to_list(char **args, t_shell *data, int quote_status, size_t i)
{
	size_t		j;
	char		*temp;

	while (++i < data->tok.words)
	{
		j = -1;
		while (args[i][++j])
		{
			temp = &args[i][j];
			isquote(args[i][j], &quote_status);
			if (quote_status == IN_DOUBLE_QUOTES)
				j += dquotes(temp + 1, data);
			else if (quote_status == IN_SINGLE_QUOTES)
				j += squotes(temp + 1, data);
			else
				j += uquote(temp, data);
		}
		if (args[i])
=======
			uquote(head->sequence, data);
		if (head->next && (head->next->sequence[0] == ' ' || head->sequence[ft_strlen(head->sequence) - 1] == ' '))
>>>>>>> 5adef0d8bc1aaa7af68246a2dfa7d918219fa363
		{
			if (quoteadd_back(data->sequences,
					quotenew(NULL, PUT_SPACE_HERE, 0)) == -1)
				return (-1);
		}
		head = head->next;
	}
	return (0);
}

t_quotes	**get_token_list(t_shell *data, size_t i)
{
	t_quotes	**list;
	t_quotes	*new;
	int			quote_status;
	int			prev_status;
	size_t		pos;

	list = malloc(sizeof(t_quotes **));
	if (!list)
		return (NULL);
	*list = NULL;
	pos = 0;
	quote_status = 0;
	isquote(data->raw_input[0], &quote_status);
	while (data->raw_input[++i])
	{
		prev_status = quote_status;
		isquote(data->raw_input[i], &quote_status);
		if (quote_status != prev_status || !data->raw_input[i + 1])
		{
			if (!data->raw_input[i + 1] || (prev_status && !quote_status))
				i++;
			new = quotenew(&data->raw_input[pos], 0, i - pos);
			if (!new)
				return (NULL);
			quoteadd_back(list, new);
			while (pos < i - 1)
				isquote(data->raw_input[pos++], &quote_status);
			pos++;
		}
		if (!data->raw_input[i])
			break ;
	}
	return (list);
}

int	tokenize(t_shell *data)
{
	t_quotes	**temp_list;

	if (check_quotes(data) == -1)
		return (-1);
	temp_list = get_token_list(data, -1);
	add_tokens_to_list(temp_list, data);
	free_sequences(temp_list);
	return (0);
}
