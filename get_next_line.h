/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:54:16 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/24 20:17:30 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

struct							s_buffer
{
	int							fd;
	char						buf[BUFFER_SIZE];
	size_t						len;
};
typedef struct s_buffer			t_buffer;

struct							s_buffer_list
{
	t_buffer					*list;
	size_t						len;
};
typedef struct s_buffer_list	t_buffer_list;

char		*get_next_line(int fd);
t_buffer	*find(t_buffer_list list, int fd);
ssize_t		read_file(t_buffer *buf);
t_buffer	*update_list(t_buffer_list list, int fd);
void		free_list(t_buffer_list list);
char		*get_line(t_buffer *buf);

#endif
