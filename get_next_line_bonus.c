/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:54:55 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/29 16:22:10 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	read_file(t_buffer *buf)
{
	ssize_t	len;

	len = read(buf->fd, buf->buf + buf->len, BUFFER_SIZE - buf->len);
	if (len > 0)
		buf->len += len;
	return (len);
}

char	*duplicate_and_shift(t_buffer *buf, size_t n)
{
	char	*dup;
	size_t	dup_len;

	if (buf == NULL)
		return (NULL);
	dup_len = 0;
	while (dup_len < n && buf->buf[dup_len])
		dup_len++;
	dup = malloc((dup_len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_memmove(dup, buf->buf, dup_len);
	dup[dup_len] = '\0';
	buf->len -= dup_len;
	ft_memmove(buf->buf, buf->buf + dup_len, buf->len);
	return (dup);
}

// return concatenated string
// arguments must be freeable
// arguments are always freed
char	*ft_strjoin_consume(char *s1, char *s2)
{
	char	*buf;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	while (s1 && s1[len1])
		len1++;
	len2 = 0;
	while (s2 && s2[len2])
		len2++;
	buf = malloc((len1 + len2 + 1) * sizeof(char));
	if (buf == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_memmove(buf, s1, len1);
	ft_memmove(buf + len1, s2, len2);
	buf[len1 + len2] = '\0';
	free(s1);
	free(s2);
	return (buf);
}

char	*get_line(t_buffer *buf)
{
	size_t	copy_len;
	char	*line;
	char	*newline_addr;

	line = NULL;
	while (read_file(buf) > 0 || buf->len > 0)
	{
		newline_addr = ft_memchr(buf->buf, '\n', buf->len);
		if (newline_addr == NULL)
			copy_len = buf->len;
		else
			copy_len = newline_addr - buf->buf + 1;
		line = ft_strjoin_consume(line, duplicate_and_shift(buf, copy_len));
		if (line == NULL || newline_addr != NULL)
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buffer_list	*list;
	t_buffer_list			*node;
	char					*line;
	size_t					len;

	node = find_node(list, fd);
	if (node == NULL)
	{
		node = push_front_new_node(&list, fd);
		if (node == NULL)
			return (NULL);
	}
	line = get_line(node->buf);
	len = 0;
	while (line && line[len])
		len++;
	if (line == NULL || ft_memchr(line, '\n', len) == NULL)
		remove_node(&list, fd);
	return (line);
}
