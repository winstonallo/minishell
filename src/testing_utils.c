/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:16:38 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 22:11:33 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_quote_list(t_quotes **sequences)
{
	t_quotes	*head;

	head = *sequences;
	while (head != NULL)
	{
		if (head->status == IN_DOUBLE_QUOTES)
			printf("Double Quoted Sequence: %s\n", head->sequence);
		else if (head->status == IN_SINGLE_QUOTES)
			printf("Single Quoted Sequence: %s\n", head->sequence);
		else if (head->status == UNQUOTED)
			printf("Unquoted Sequence: %s\n", head->sequence);
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
		else if (head->special_character == 0)
			printf("No special character: %s\n", head->sequence);
		else if (head->special_character == PIPE)
			printf("Pipe character: %d\n", head->special_character);
		else if (head->special_character == OUTPUT_REDIRECTION)
			printf("Output redirection character: %d\n",
				head->special_character);
		else if (head->special_character == INPUT_REDIRECTION)
			printf("Input redirection character: %d\n",
				head->special_character);
		head = head->next;
	}
}

void	print_cmd_tables(t_cmd_table **cmd_tables)
{
	t_cmd_table	*head;

	head = *cmd_tables;
	while (head)
	{
		if (head->args)
		{
			for (int i = 0; head->args[i]; i++)
				printf("head->args[%d]: %s\n", i, head->args[i]);
			if (head->infile != NO_FD)
				printf("\nINFILE FD = %d\n", head->infile);
			if (head->outfile != NO_FD)
				printf("\nOUTFILE FD = %d\n", head->outfile);	
		}
		else if (head->pipe == PIPE)
			printf("\nTHIS NODE IS A PIPE DELIMITER\n");
		head = head->next;
	}
}
