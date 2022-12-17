/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:46:26 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/17 07:56:13 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putstr(int fd, char *s)
{
	int	i;

	i = -1;
	if (s == NULL)
		ft_putstr(fd, "(null)");
	while (s[++i])
		write(fd, &s[i], 1);
}

void	ft_dprintf(int fd, char *s, ...)
{
	va_list	ap;
	int		i;

	i = -1;
	va_start(ap, s);
	while (s[++i])
	{
		if (s[i] == '%')
		{
			if (s[++i] == 's')
				ft_putstr(fd, va_arg(ap, char *));
		}
		else
			ft_putchar_fd(fd, s[i]);
	}
	va_end(ap);
}
