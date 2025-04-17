/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:59:54 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/17 20:10:47 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char *build_buffer(char *buffer, char *buffer_res)
{
	char *temp;
	
	if (!buffer)
		buffer = ft_strdup(buffer_res);
	else
	{
		temp = ft_strjoin(buffer, buffer_res);
		free(buffer);
		buffer = temp;
	}
	return (buffer);
}
int	has_new_line(char *buffer_res)
{
	while (*buffer_res)
	{
		if (*buffer_res == '\n')
			return (1);
		buffer_res++;
	}
	return (0);
}

char *read_buffer(int fd, char *buffer)
{
	char *buffer_res;
	ssize_t	bytes_read;

	bytes_read = 1;
	buffer_res = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer_res)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer_res, BUFFER_SIZE);
		if (bytes_read < 0 || (!bytes_read && !buffer))
		{
			free(buffer_res);
			return (NULL);
		}	
		if (!bytes_read)
			break;
		buffer_res[bytes_read] = '\0';
		buffer = build_buffer(buffer, buffer_res);
		if (has_new_line(buffer_res))
			break;
	}
	free(buffer_res);
	return (buffer);
}

char *get_next_line(int fd)
{
	static	char *buffer;
	char *line;
	char *remainder;
	int		new_line_i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer || !buffer[0])
	{
		free(buffer);
		return (NULL);
	}
	new_line_i = 0;
	while (buffer[new_line_i] && buffer[new_line_i] != '\n')
		new_line_i++;
	if (new_line_i < (int)(ft_strlen(buffer) - 1))
	{
		remainder = ft_strdup(&buffer[new_line_i + 1]);
		buffer[new_line_i + 1] = '\0';
		line = ft_strdup(buffer);
		if (!remainder || !line)
		{
			if (remainder)
				free(remainder);
			if (line)
				free(line);
			free(buffer);
			return (NULL);
		}
		free(buffer);
		buffer = remainder;
	}
	else
	{
		line = ft_strdup(buffer);
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
/*
#include <fcntl.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *s;
	while ((s = get_next_line(fd)))
	{
		printf("LINE: %s", s);
		free(s);
	}
	close(fd);
}
*/