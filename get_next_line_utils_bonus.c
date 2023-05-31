/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:55:36 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/31 16:57:07 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// create a new node and add it to the head of the list
// the return value is the created node
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
	buf->has_read_error = false;
	node = malloc(sizeof(t_buffer_list));
	if (node == NULL)
		return (NULL);
	node->buf = buf;
	node->next = *list;
	node->prev = NULL;
	if (*list != NULL)
		(*list)->prev = node;
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

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*addr;

	if (dst == src || len == 0)
		return (dst);
	addr = dst;
	if (dst < src)
	{
		while (len--)
			*(unsigned char *)dst++ = *(unsigned char *)src++;
	}
	else
	{
		dst += len - 1;
		src += len - 1;
		while (len--)
			*(unsigned char *)dst-- = *(unsigned char *)src--;
	}
	return (addr);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		chr;

	str = s;
	chr = c;
	while (n && *str != chr)
	{
		str++;
		n--;
	}
	if (n && *str == chr)
		return ((void *)str);
	return (NULL);
}
