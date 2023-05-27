/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 21:02:39 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/27 21:02:40 by kemizuki         ###   ########.fr       */
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
		return (NULL);
	ft_memmove(buf, s1, len1);
	ft_memmove(buf + len1, s2, len2);
	buf[len1 + len2] = '\0';
	free(s1);
	free(s2);
	return (buf);
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

char	*ft_strndup(const char *str, size_t n)
{
	char	*buf;
	size_t	substr_len;

	if (str == NULL)
		return (NULL);
	substr_len = 0;
	while (substr_len < n && str[substr_len])
		substr_len++;
	buf = malloc((substr_len + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	buf[substr_len] = '\0';
	while (substr_len--)
		buf[substr_len] = str[substr_len];
	return (buf);
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
