/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:59:22 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/11 11:12:07 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	count(char *s, char c)
{
	t_split	sp;

	sp.j = 0;
	sp.i = 0;
	while (s[sp.i] && s[sp.i] == c)
		sp.i++;
	while (s[sp.i])
	{
		if (s[sp.i] == 39 || s[sp.i] == 34)
			sp.k = s[sp.i];
		else
			sp.k = c;
		sp.next_stop = ft_strchr(&s[sp.i + 1], sp.k);
		sp.i += sp.next_stop - &s[sp.i];
		if (sp.k != c)
			sp.i += 2;
		sp.j++;
		while (s[sp.i] && s[sp.i] == c)
			sp.i++;
	}
	return (sp.j);
}

char	**ft_fill(t_split sp, char *s, char c)
{
	sp.j = 0;
	while (s[sp.i])
	{
		sp.wordlen = 0;
		sp.start = &s[sp.i];
		if (s[sp.i] == 39 || s[sp.i] == 34)
		{
			sp.start = &s[sp.i + 1];
			sp.next_stop_char = s[sp.i];
			sp.wordlen = -1;
		}
		else
			sp.next_stop_char = c;
		sp.next_stop = ft_strchr(&s[sp.i + 1], sp.next_stop_char);
		sp.wordlen += sp.next_stop - &s[sp.i];
		sp.i += sp.wordlen;
		if (sp.next_stop_char != c)
			sp.i += 2;
		sp.str[sp.j++] = ft_substr(sp.start, 0, sp.wordlen);
		while (s[sp.i] && s[sp.i] == c)
			sp.i++;
	}
	sp.str[sp.j] = NULL;
	return (sp.str);
}

char	**ft_split(char *s, char c)
{
	t_split	sp;
	int		x;

	x = 0;
	sp.str = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!sp.str)
		return (NULL);
	sp.i = 0;
	while (s[sp.i] && s[sp.i] == c)
		sp.i++;
	sp.str = ft_fill(sp, s, c);
	return (sp.str);
}
