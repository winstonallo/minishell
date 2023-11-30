/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:16:38 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/28 13:19:15 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*List printing functions to check if the parsing works properly*/
void	print_quote_list(t_quotes **sequences)
{
	t_quotes	*head;

	head = *sequences;
	while (head != NULL)
	{
		if (head->status == PUT_SPACE_HERE)
			printf("Space:))\n");
		if (head->status == IN_DOUBLE_QUOTES)
			printf("Double Quoted Sequence: [%s]\n", head->sequence);
		else if (head->status == IN_SINGLE_QUOTES)
			printf("Single Quoted Sequence: [%s]\n", head->sequence);
		else if (head->status == UNQUOTED)
			printf("Unquoted Sequence: [%s]\n", head->sequence);
		head = head->next;
	}
}

void	print_op_list(t_op **opps)
{
	t_op	*head;

	head = *opps;
	while (head != NULL)
	{
		if (head->status == IN_DOUBLE_QUOTES)
			printf("Double Quoted Sequence: %s\n", head->sequence);
		else if (head->status == IN_SINGLE_QUOTES)
			printf("Single Quoted Sequence: %s\n", head->sequence);
		else if (head->status == UNQUOTED && !head->s_char)
			printf("Unquoted sequence: %s\n", head->sequence);
		else if (head->status == PUT_SPACE_HERE)
			printf("SPACE\n");
		else if (head->s_char == PIPE)
			printf("Pipe character: %d\n", head->s_char);
		else if (head->s_char == OUT_REDIR)
			printf("Output redirection character\n");
		else if (head->s_char == IN_REDIR)
			printf("Input redirection character\n");
		else if (head->s_char == APPEND)
			printf("Append signal\n");
		else if (head->s_char == HEREDOC)
			printf("Heredoc signal\n");
		head = head->next;
	}
}

void	print_cmd_tables(t_cmd_table **cmd_tables)
{
	t_cmd_table	*head;
	int			i;

	i = 0;
	head = *cmd_tables;
	while (head)
	{
		if (!head->pipe && head->args)
		{
			i = -1;
			while (head->args[++i])
				printf("head->args[%d]: %s\n", i, head->args[i]);
			if (head->infile != NO_FD)
				printf("\nINFILE FD = %d\n", head->infile);
			if (head->outfile != NO_FD)
				printf("\nOUTFILE FD = %d\n", head->outfile);
		}
		else if (head->pipe == PIPE)
			printf("\nTHIS NODE IS A PIPE DELIMITER\n\n");
		head = head->next;
	}
}

void	print_env(t_shell *data)
{
	t_env	*head;

	head = *data->env_list;
	while (head)
	{
		printf("NAME: %s\nLINE: %s\n------\n", head->name, head->line);
		head = head->next;
	}
}
