/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:54:55 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/27 21:00:31 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_buffer_list	*push_front_new_node(t_buffer_list **list, int fd)
{
	t_buffer		*buf;
	t_buffer_list	*node;

	if (list == NULL)
		return (NULL);
	buf = malloc(sizeof(t_buffer));
	if (buf == NULL)
		return (NULL);
	buf->fd = fd;
	buf->len = 0;
	node = malloc(sizeof(t_buffer_list));
	if (node == NULL)
		return (NULL);
	node->buf = buf;
	node->next = *list;
	node->prev = NULL;
	*list = node;
	return (node);
}

void	remove_node(t_buffer_list **list, int fd)
{
	t_buffer_list	*node;

	if (list == NULL)
		return ;
	node = find_node(*list, fd);
	if (node == NULL)
		return ;
	if (node->prev != NULL)
		node->prev->next = node->next;
	else
		*list = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	free(node->buf);
	free(node);
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
	ssize_t	len;
	size_t	copy_len;
	char	*line;
	char	*newline_addr;
	char	*join_src;

	line = NULL;
	len = read_file(buf);
	while (len > 0 || buf->len > 0)
	{
		newline_addr = ft_memchr(buf->buf, '\n', buf->len);
		if (newline_addr == NULL)
			copy_len = buf->len;
		else
			copy_len = newline_addr - buf->buf + 1;
		join_src = ft_strndup(buf->buf, copy_len);
		buf->len -= copy_len;
		ft_memmove(buf->buf, buf->buf + copy_len, buf->len);
		line = ft_strjoin_consume(line, join_src);
		if (line == NULL || newline_addr != NULL)
			break ;
		len = read_file(buf);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buffer_list	*list;
	t_buffer_list			*node;
	char					*line;

	node = find_node(list, fd);
	if (node == NULL)
	{
		node = push_front_new_node(&list, fd);
		if (node == NULL)
			return (NULL);
	}
	line = get_line(node->buf);
	if (line == NULL)
		remove_node(&list, fd);
	return (line);
}
