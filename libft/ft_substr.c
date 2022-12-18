/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:13:53 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/18 11:42:31 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = -1;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		return (calloc(1, 1));
	}
	str = malloc(len + 1);
	if (!str)
		return (0);
	while (++i < len)
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
