/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:55:36 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/24 21:24:14 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	read_file(t_buffer *buf)
{
	ssize_t	len;

	len = read(buf->fd, buf->buf, BUFFER_SIZE - buf->len);
	if (len > 0)
		buf->len += len;
	return (len);
}

char *get_line(t_buffer *buf)
{

}
