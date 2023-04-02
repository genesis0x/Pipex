/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:33:01 by hahadiou          #+#    #+#             */
/*   Updated: 2023/03/14 23:26:11 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
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

typedef struct s_buffer	t_line;
typedef struct s_buffer	t_read;
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

char					*get_next_line(int fd);
void					ft_dprintf(int fd, char *s, ...);
char					*ft_strjoin(char const *s1, char const *s2);
char					**ft_split(char *s, char c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
size_t					ft_strlen(const char *s);
void					*ft_memcpy(void *dst, const void *src, size_t n);

#endif
