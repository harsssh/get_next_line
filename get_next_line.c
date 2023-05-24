/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:54:55 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/24 20:17:35 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_list(t_buffer_list l)
{
	while (l.list--)
		free(l.list + l.len);
}

t_buffer	*update_list(t_buffer_list l, int fd)
{
	t_buffer	*buf;
	t_buffer	*new_list;
	size_t		i;

	buf = malloc(sizeof(t_buffer));
	if (buf == NULL)
		return (NULL);
	buf->fd = fd;
	buf->len = 0;
	new_list = malloc((l.len + 1) * sizeof(t_buffer_list));
	if (new_list == NULL)
		return (NULL);
	i = 0;
	while (i < l.len)
	{
		new_list[i] = l.list[i];
		i++;
	}
	new_list[i++] = *buf;
	free_list(l);
	l.list = new_list;
	l.len = i;
	return (buf);
}

t_buffer	*find(t_buffer_list l, int fd)
{
	t_buffer	*head;

	head = l.list;
	while (l.len--)
	{
		if (fd == head->fd)
			return (head);
		head++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_buffer_list	list;
	t_buffer				*buf;
	ssize_t					len;

	//static t_buffer_list	list = {NULL, 0};
	buf = find(list, fd);
	if (buf == NULL)
		buf = update_list(list, fd);
	return (get_line(buf));
}
