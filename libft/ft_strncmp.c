/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:42:09 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/11 11:12:15 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*b;

	i = 0;
	p = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while ((p[i] || b[i]) && (i < n))
	{
		if (p[i] < b[i])
			return (-1);
		if (p[i] > b[i])
			return (1);
		i++;
	}
	return (0);
}
