/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:36:03 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/17 19:37:41 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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