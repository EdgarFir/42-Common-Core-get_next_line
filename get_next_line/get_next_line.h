/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:59:45 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/18 02:07:54 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen_chr(const char *s, char c);
char	*build_buffer(char *buffer, char *buffer_res, ssize_t bytes_read);
int		has_new_line(char *buffer_res);
char	*read_buffer(int fd, char *buffer);
char	*clean_all(char *buffer, char *line, char *remainder);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif