/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:46:28 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/17 07:50:58 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include <unistd.h>

void	ft_dprintf(int fd, char *s, ...);
void	ft_putchar_fd(int fd, char c);
void	ft_putstr(int fd, char *s);
void	ft_dprintf(int fd, char *s, ...);

#endif