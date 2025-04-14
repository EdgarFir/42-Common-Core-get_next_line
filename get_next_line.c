/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:09:28 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/14 00:11:42 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int search_new_line(char *buffer)
{
	int i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] == '\0' || buffer[i] == '\n')
			return (i);
	}
	return (-1);
}

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	len = 0;
	if (size <= dst_len)
		return (src_len + size);
	else
		len = dst_len + src_len;
	while (src[i] && (dst_len + 1) < size)
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
	}
	dst[dst_len] = '\0';
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
char	*ft_strdup(char *s, int total)
{
	char	*new_s;
	int		i;
	//int		len;

	//len = ft_strlen(s);
	new_s = (char *)malloc(sizeof(char) * total);
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < total)
	{
		new_s[i] = s[i];
		printf("%c", new_s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char *get_next_line(int fd)
{	
	static char	*buffer;
	char	*buffer_read;
	char	*line;
	int			final_ind;
	int			total;
	size_t		bytes_read;

	buffer = NULL;
	line = NULL;
	buffer_read = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	while (bytes_read = read(fd, buffer_read, BUFFER_SIZE))
	{
		//final_ind = search_new_line(buffer);
		if (!line)
			line = buffer_read;
		else
			ft_memcpy(line, buffer_read, bytes_read);
		total += bytes_read;
	}
	printf("%s", line);
	return ("ABC");
	//return ("BAa");
	 
}

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY);
	char *s;

	s = get_next_line(fd);
	//printf("%s\n", s);
	
}