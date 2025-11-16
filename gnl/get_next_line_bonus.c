/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:59:54 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/19 11:39:45 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		return (clean_all(buffer, buffer_res, NULL));
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

char	*clean_all(char *buffer1, char *buffer2, char *buffer3)
{
	if (buffer1)
	{
		free(buffer1);
		buffer1 = NULL;
	}
	if (buffer2)
	{
		free(buffer2);
		buffer2 = NULL;
	}
	if (buffer3)
	{
		free(buffer3);
		buffer3 = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buf[10000];
	char		*ln;
	char		*rem;
	int			nl_i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf[fd] = read_buffer(fd, buf[fd]);
	if (!buf[fd] || !buf[fd][0])
		return (clean_all(buf[fd], NULL, NULL));
	nl_i = ft_strlen_chr(buf[fd], '\n');
	if (nl_i < (int)(ft_strlen_chr(buf[fd], 0) - 1))
	{
		rem = ft_strdup(&buf[fd][nl_i + 1]);
		ln = ft_substr(buf[fd], 0, nl_i + 1);
		if (!rem || !ln)
			return (free(buf[fd]), buf[fd] = NULL, clean_all(0, rem, ln));
		free(buf[fd]);
		buf[fd] = rem;
		return (ln);
	}
	ln = ft_strdup(buf[fd]);
	return (free(buf[fd]), buf[fd] = NULL, ln);
}
