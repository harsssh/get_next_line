/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:22:34 by kemizuki          #+#    #+#             */
/*   Updated: 2023/06/01 17:36:55 by kemizuki         ###   ########.fr       */
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
	buf->read_failed = false;
	node = malloc(sizeof(t_buffer_list));
	if (node == NULL)
	{
		free(buf);
		return (NULL);
	}
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
	node = *list;
	while (node != NULL && node->buf->fd != fd)
		node = node->next;
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

char	*ft_strjoin(const char *s1, const char *s2)
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
	if (buf == NULL)
		return (NULL);
	ft_memmove(buf, s1, len1);
	ft_memmove(buf + len1, s2, len2);
	buf[len1 + len2] = '\0';
	return (buf);
}
