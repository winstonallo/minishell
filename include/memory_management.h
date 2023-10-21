/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:01:08 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/21 19:20:48 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_MANAGEMENT_H
# define MEMORY_MANAGEMENT_H

# include "lists.h"
# include "structs.h"

void		free_paths(t_path **stack_a);
void		free_sequences(t_quotes **sequences);
void		free_array(char **arr);
void		wipe(t_shell *data);

#endif