/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:02:13 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 22:11:45 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTING_UTILS_H
# define TESTING_UTILS_H

# include "lists.h"

void	print_quote_list(t_quotes **sequences);
void	print_op_list(t_op **opps);
void	print_cmd_tables(t_cmd_table **cmd_tables);

#endif