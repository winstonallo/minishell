/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:43 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/17 16:38:51 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// join and free
char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

// delete line find
char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	// find len of first line
	while (buffer[i] && buffer[i] != '\n')
		i++;
	// if eol == \0 return NULL
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	// len of file - len of firstline + 1
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	// line == buffer
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

// take line for return
char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	// if no line return NULL
	if (!buffer[i])
		return (NULL);
	// go to the eol
	while (buffer[i] && buffer[i] != '\n')
		i++;
	// malloc to eol
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	// line = buffer
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	// if eol is \0 or \n, replace eol by \n
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	// malloc if res dont exist
	if (!res)
		res = ft_calloc(1, 1);
	// malloc buffer
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		// while not eof read
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		// 0 to end for leak
		buffer[byte_read] = 0;
		// join and free
		res = ft_free(res, buffer);
		// quit if \n find
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*gnl(int fd)
{
	static char	*buffer;
	char		*line;

	// error handling
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}

int	checkcmd(t_shell *data)
{
	if (!data->cmd_table || !*data->cmd_table || !(*data->cmd_table)->args
		|| !(*data->cmd_table)->args[0])
		return (SUCCESS);
	if (ft_strncmp((*data->cmd_table)->args[0], "exit", 5) == 0)
		return (myexit(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "export", 6) == 0)
		return (export(data));
	else if (ft_strncmp((*data->cmd_table)->args[0], "cd", 3) == 0)
		return (cd(data));
	return (COMMAND_NOT_FOUND);
}

/**
 * The function reads user input, processes it for quotes, expands sequences, 
 * parses special characters, creates a command table, 
 * and finds the command to execute.
 */
int	read_input(t_shell *data)
{
	add_history(data->raw_input);
	if (parse_for_quotes(data) == -1)
		return (-1);
	if (expand(data) == -1)
		return (-1);
	if (parse_special_char(data) == -1)
		return (-1);
	if (get_command_table(data) == -1)
		return (-1);
	if (checkcmd(data) != COMMAND_NOT_FOUND)
		return (SUCCESS);
	execute_command(data);
	return (0);
}

/**
 * The function "check_status" checks the exit status of a shell command 
 * and returns the appropriate value.
 * @return the value of `data->exit`.
 */
int	check_status(t_shell *data)
{
	if (data->exit == COMMAND_NOT_FOUND)
	{
		ft_putstr_fd(data->raw_input, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (COMMAND_NOT_FOUND);
	}
	else if (data->exit == EXIT)
		return (EXIT);
	return (data->exit);
}

/**
 * The function "loop" reads input from the user, processes it, and repeats 
 * the process until an exit condition is met.
 * 
 * @param data The parameter "data" is of type "t_shell", which is a struct
 *  that contains information and variables related to the shell program.
 * 
 * @return an integer value. If the condition `first_read(data) == EXIT` 
 * is true, then the function will return the value of `EXIT`. Otherwise,
 * if any of the subsequent conditions are true, the function will return 
 * the value of `data->exit`. If none of the conditions are true, the function
 * will return 0.
 */
int	loop(t_shell *data)
{
	while (1)
	{
		if (initialize_sequences(data) == -1)
			return (data->exit);
		if (isatty(fileno(stdin)))
			data->raw_input = readline(data->prompt);
		else
		{
			char *line;
			line = gnl(fileno(stdin));
			data->raw_input = ft_strtrim(line, "\n");
			free(line);
		}
		if (!data->raw_input)
			return (myexit(data));
		if (!data->raw_input[0])
		{
			wipe(data);
			continue ;
		}
		if (read_input(data) == -1)
		{
			wipe(data);
			continue ;
		}
		if (check_status(data) == EXIT)
			return (EXIT);
		wipe(data);
	}
	return (0);
}
