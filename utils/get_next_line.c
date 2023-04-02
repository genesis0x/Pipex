/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:13:19 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/11 11:12:26 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	free_buffer(t_read *prb)
{
	if (prb->buf != NULL)
	{
		free(prb->buf);
		prb->buf = NULL;
	}
}

static char	*ft_realloc(t_line *line)
{
	char	*new_buf;
	size_t	new_size;

	new_size = line->size + 1;
	new_buf = malloc((new_size + 1) * sizeof(char));
	if (line->buf)
	{
		if (new_buf)
			ft_memcpy(new_buf, line->buf, line->size);
		free(line->buf);
	}
	line->buf = new_buf;
	line->size = new_size;
	return (new_buf);
}

static int	read_file(int fd, t_read *reserve)
{
	if (!reserve->buf)
		reserve->buf = malloc(BUFFER_SIZE);
	if (reserve->pos >= reserve->size)
	{
		reserve->size = read(fd, reserve->buf, BUFFER_SIZE);
		if (reserve->size < 1)
			return (0);
		reserve->pos = 0;
	}
	return (reserve->buf[reserve->pos++]);
}

static int	put_line(t_line *line, char c)
{
	if (line->pos >= line->size)
	{
		if (ft_realloc(line) == NULL)
			return (0);
	}
	line->buf[line->pos++] = c;
	if (c == '\n')
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	int				c;
	t_line			line;
	static t_read	reserve;

	if (fd < 0 || read(fd, line.buf, 0) < 0)
		return (0);
	line.buf = 0;
	line.pos = 0;
	line.size = 0;
	while (1)
	{
		c = read_file(fd, &reserve);
		if (c == 0)
			break ;
		if (put_line(&line, c) == 0)
			break ;
	}
	if (line.pos == 0)
		free_buffer(&reserve);
	else
		line.buf[line.pos] = 0;
	return (line.buf);
}
