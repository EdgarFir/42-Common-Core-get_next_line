/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:59:54 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/19 01:08:00 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (!buffer_res)
		return (0);
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
			return (clean_all(buffer, buffer_res, 0));
		if (!bytes_read)
			break ;
		buffer = build_buffer(buffer, buffer_res, bytes_read);
		if (!buffer)
			break ;
		if (has_new_line(buffer_res))
			break ;
	}
	free(buffer_res);
	return (buffer);
}

char	*clean_all(char *buffer, char *line, char *remainder)
{
	if (buffer)
		free(buffer);
	if (line && line != buffer && line != remainder)
		free(line);
	if (remainder && remainder != buffer && remainder != line)
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
	if (!buffer || !buffer[0])
		return (clean_all(buffer, 0, 0));
	new_line_i = ft_strlen_chr(buffer, '\n');
	if (new_line_i < (int)(ft_strlen_chr(buffer, 0) - 1))
	{
		remainder = ft_strdup(&buffer[new_line_i + 1]);
		line = ft_substr(buffer, 0, new_line_i + 1);
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
