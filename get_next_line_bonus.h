/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:23:02 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/31 16:56:52 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>

struct							s_buffer
{
	int							fd;
	char						buf[BUFFER_SIZE];
	size_t						len;
	bool						has_read_error;
};
typedef struct s_buffer			t_buffer;

struct							s_buffer_list
{
	struct s_buffer				*buf;
	struct s_buffer_list		*next;
	struct s_buffer_list		*prev;
};
typedef struct s_buffer_list	t_buffer_list;

ssize_t			read_file(t_buffer *buf);
char			*duplicate_and_shift(t_buffer *buf, size_t n);
char			*ft_strjoin_consume(char *s1, char *s2);
char			*get_next_line(int fd);
char			*get_line(t_buffer *buf);

t_buffer_list	*push_front_new_node(t_buffer_list **list, int fd);
void			remove_node(t_buffer_list **list, int fd);
t_buffer_list	*find_node(t_buffer_list *list, int fd);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);

#endif
