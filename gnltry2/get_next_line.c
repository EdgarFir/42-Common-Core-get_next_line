/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:59:54 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/17 13:39:40 by edfreder         ###   ########.fr       */
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_p;
	unsigned char	*src_p;

	if (!dest && !src)
		return (NULL);
	dest_p = (unsigned char *)dest;
	src_p = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest_p[i] = src_p[i];
		i++;
	}
	return (dest);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	new_str[s1_len + s2_len] = '\0';
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	int		i;
	int		len;

	len = ft_strlen(s);
	new_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	mem_to_aloc;
	void	*ptr;

	if (size != 0 && nmemb > (size_t)(-1) / size)
		return (NULL);
	mem_to_aloc = 1;
	mem_to_aloc = nmemb * size;
	ptr = malloc(mem_to_aloc);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, mem_to_aloc);
	return (ptr);
}

char *read_buffer(int fd, char *buffer)
{
	char *buffer_res;
	ssize_t	bytes_read;
	int i;

	bytes_read = 1;
	buffer_res = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer_res, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
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
	
	buffer = read_buffer(fd, buffer);
	//printf("BUFFER LEN: %i", ft_strlen(buffer));
	new_line_i = 0;
	while (buffer[new_line_i] && buffer[new_line_i] != '\n')
	{
		new_line_i++;
	}
	printf("NEW_LINE: %i ", new_line_i);
	printf("BUFFER LEN: %i ", ft_strlen(buffer));
	printf("REMAINDER: %s ", &buffer[new_line_i + 1]);
	if (new_line_i < ft_strlen(buffer) - 1)
	{
		remainder = ft_strdup(&buffer[new_line_i + 1]);
		line = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - new_line_i));
		buffer[new_line_i + 1] = '\0';
		line = ft_strdup()
		
	}
	// ABC /nDE F
	// 012 345  6
	return (line);
}

#include <fcntl.h>
int main()
{
	int fd = open("../tests/test2.txt", O_RDONLY);
	char *s;
	s = get_next_line(fd);
	printf("LINE: %s", s);
	free(s);
	close(fd);
}