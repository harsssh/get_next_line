/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:54:55 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/31 19:19:14 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	read_file(t_buffer *buf)
{
	ssize_t	len;

	len = read(buf->fd, buf->buf + buf->len, BUFFER_SIZE - buf->len);
	if (len > 0)
		buf->len += len;
	else if (len < 0)
		buf->read_failed = true;
	return (len);
}

char	*extract_prefix_and_shift(t_buffer *buf, size_t n)
{
	char	*prefix;
	size_t	len;

	if (buf == NULL)
		return (NULL);
	len = 0;
	while (len < n && buf->buf[len])
		len++;
	prefix = malloc((len + 1) * sizeof(char));
	if (prefix == NULL)
		return (NULL);
	ft_memmove(prefix, buf->buf, len);
	prefix[len] = '\0';
	buf->len -= len;
	ft_memmove(buf->buf, buf->buf + len, buf->len);
	return (prefix);
}

// arguments are always freed
char	*ft_strjoin_consume(char *s1, char *s2)
{
	char	*buf;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = 0;
	while (s1 && s1[len1])
		len1++;
	len2 = 0;
	while (s2 && s2[len2])
		len2++;
	buf = malloc((len1 + len2 + 1) * sizeof(char));
	if (buf != NULL)
	{
		ft_memmove(buf, s1, len1);
		ft_memmove(buf + len1, s2, len2);
		buf[len1 + len2] = '\0';
	}
	free(s1);
	free(s2);
	return (buf);
}

char	*get_line(t_buffer *buf)
{
	size_t	copy_len;
	char	*line;
	char	*newline_addr;
	char	*buf_prefix;

	line = NULL;
	while (buf->len > 0 || read_file(buf) > 0)
	{
		newline_addr = ft_memchr(buf->buf, '\n', buf->len);
		if (newline_addr == NULL)
			copy_len = buf->len;
		else
			copy_len = newline_addr - buf->buf + 1;
		buf_prefix = extract_prefix_and_shift(buf, copy_len);
		line = ft_strjoin_consume(line, buf_prefix);
		if (line == NULL || newline_addr != NULL)
			break ;
	}
	if (buf->read_failed)
	{
		free(line);
		line = NULL;
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
