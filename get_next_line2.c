/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:12:33 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/14 03:17:51 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
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
t_lines *create_struct(char *remainded, char *buffer)
{
	t_lines *new_node;
	char *new_content;

	new_node = (t_lines *)malloc(sizeof(t_lines));
	if (!new_node)
		return (NULL);
	if (remainded)
	{
		new_content = malloc(sizeof(char) * (ft_strlen(remainded) + ft_strlen(buffer) + 1));
		ft_memcpy(new_content, remainded, ft_strlen(remainded));
		ft_memcpy(new_content + ft_strlen(remainded), buffer, ft_strlen(buffer));
		new_content[ft_strlen(remainded) + ft_strlen(buffer)] = '\0';
		new_node->content = new_content;
	}
	else
		new_node->content = ft_strdup(buffer);
	new_node->next = NULL;
	return (new_node);
}
void add_back(t_lines **line, t_lines *new_node)
{
	t_lines	*ptr;

	if (!(*line))
		*line = new_node;
	else
	{
		ptr = *line;
		int i = 0;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
			i++;
		}
		ptr->next = new_node;
	}
}

void print_line(t_lines *line)
{
	while (line)
	{
		printf("%s", line->content);
		line = line->next;
	}
}


int search_new_line(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*create_line(t_lines *line, int total)
{
	char	*created_line;
	int		actual_len;
	size_t	content_len;

	created_line = malloc(sizeof(char) * (total + 1));
	if (!created_line)
		return (NULL);
	actual_len = 0;
	while (line)
	{
		content_len = ft_strlen(line->content);
		ft_memcpy(created_line + actual_len, line->content, ft_strlen(line->content));
		actual_len += content_len;
		line = line->next;
	}
	//printf("%i\n", actual_len);
	created_line[actual_len] = '\0';
	return (created_line);
}

char *get_next_line(int fd)
{
	t_lines *line;
	t_lines *new_node;
	char	*buffer;
	ssize_t bytes_read;
	static char	*remainder;
	int		new_line_i;
	int		total;

	line = NULL;
	remainder = NULL;
	total = 0;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		new_line_i = search_new_line(buffer);
		if (new_line_i >= 0)
			buffer[new_line_i + 1] = '\0';
		else
			buffer[bytes_read] = '\0';
		new_node = create_struct(remainder, buffer);
		if (!new_node)
			return (NULL);
		add_back(&line, new_node);
		if (new_line_i >= 0 && new_line_i < bytes_read - 1)
		{
			//printf("CARALHOOOOO!");
			total += new_line_i;
			remainder = ft_strdup(buffer + new_line_i);
		}
		else
			total += bytes_read;
		return (create_line(line, total));
	}
	//create_line(line, total);
	//printf("tOTAL: %i\n", total);
	return (NULL);
}

int main(int argc, char *argv[])
{
	(void)argc;
	int fd = open(argv[1], O_RDONLY);
	char *s;
	while ((s = get_next_line(fd)))
	{
		printf("%s", s);
	}
}