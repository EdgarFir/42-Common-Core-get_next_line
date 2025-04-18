/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:59:54 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/18 01:51:37 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*build_buffer(char *buffer, char *buffer_res, ssize_t bytes_read)
{
	char	*temp;

	buffer_res[bytes_read] = '\0';
	if (!buffer)
		return (ft_strdup(buffer_res));
	temp = ft_strjoin(buffer, buffer_res);
	free(buffer);
	buffer = temp;
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

char	*read_buffer(int fd, char *buffer)
{
	char	*buffer_res;
	ssize_t	bytes_read;

	bytes_read = 1;
	buffer_res = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer_res)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer_res, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer_res);
			free(buffer);
			return (NULL);
		}
		if (!bytes_read)
			break ;
		buffer = build_buffer(buffer, buffer_res, bytes_read);
		if (!buffer || has_new_line(buffer_res))
			break ;
	}
	free(buffer_res);
	return (buffer);
}

char	*clean_all(char *buffer, char *line, char *remainder)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	if (line)
		free(line);
	if (remainder)
		free(remainder);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*remainder;
	int			new_line_i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	new_line_i = ft_strlen_chr(buffer, '\n');
	if (new_line_i < (int)(ft_strlen_chr(buffer, 0) - 1))
	{
		remainder = ft_strdup(&buffer[new_line_i + 1]);
		buffer[new_line_i + 1] = '\0';
		line = ft_strdup(buffer);
		if (!remainder || !line)
			return (clean_all(0, line, remainder));
		free(buffer);
		buffer = remainder;
		return (line);
	}
	line = ft_strdup(buffer);
	free(buffer);
	buffer = NULL;
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
	}
	printf("%s\n", s);
	close(fd);
}
*/