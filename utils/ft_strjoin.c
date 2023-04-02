/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:41:39 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/11 11:12:11 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		len1;
	int		len2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	len1 = strlen(s1);
	len2 = strlen(s2);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	while (++i < len1)
		new[i] = s1[i];
	j = -1;
	while (++j < len2)
	{
		new[i] = s2[j];
		i++;
	}
	new[i] = '\0';
	return (new);
}
