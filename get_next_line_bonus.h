/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:36:20 by kemizuki          #+#    #+#             */
/*   Updated: 2023/06/01 17:36:38 by kemizuki         ###   ########.fr       */
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
	bool						read_failed;
};
typedef struct s_buffer			t_buffer;

struct							s_buffer_list
{
	struct s_buffer				*buf;
	struct s_buffer_list		*next;
	struct s_buffer_list		*prev;
};
typedef struct s_buffer_list	t_buffer_list;

char			*get_next_line(int fd);

t_buffer_list	*push_front_new_node(t_buffer_list **list, int fd);
void			remove_node(t_buffer_list **list, int fd);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
char			*ft_strjoin(const char *s1, const char *s2);

#endif
