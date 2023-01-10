/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:38:40 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/10 16:18:51 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
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
typedef t_buffer		t_line;
typedef t_buffer		t_read;
typedef struct s_split	t_split;

struct					s_buffer
{
	char				*buf;
	size_t				pos;
	size_t				size;
};

struct					s_split
{
	char				k;
	int					i;
	int					j;
	int					wordlen;
	char				next_stop_char;
	char				*next_stop;
	char				**str;
	char				*start;
};

size_t					ft_strlen(const char *s);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					ft_dprintf(int fd, char *s, ...);
char					*ft_strnstr(const char *h, const char *n, size_t len);
char					*ft_substr(char const *s, unsigned int st, size_t len);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strjoin(char const *s1, char const *s2);
char					**ft_split(char *s, char c);
char					*get_next_line(int fd);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
