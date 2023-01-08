/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:41:50 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/08 19:16:01 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
typedef struct s_buffer	t_buffer;

struct s_buffer
{
	char			*buf;
	size_t			pos;
	size_t			size;
};

typedef t_buffer	t_line;
typedef t_buffer	t_read;

char				*get_next_line(int fd);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				free_buffer(t_read *prb);

#endif
