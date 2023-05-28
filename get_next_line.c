/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:54:55 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/28 13:17:39 by kemizuki         ###   ########.fr       */
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
	if (buf == NULL)
		return (NULL);
	ft_memmove(dup, buf->buf, dup_len);
	dup[dup_len] = '\0';
	buf->len -= dup_len;
	ft_memmove(buf->buf, buf->buf + dup_len, buf->len);
	return (dup);
}

t_buffer_list	*find_node(t_buffer_list *list, int fd)
{
	t_buffer_list	*head;

	head = list;
	while (head)
	{
		if (head->buf->fd == fd)
			return (head);
		head = head->next;
	}
	return (NULL);
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
