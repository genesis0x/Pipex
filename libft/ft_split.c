/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:59:22 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/18 11:49:17 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(char *s, char c)
{
	int		i;
	int		count;
	char	k;
	char	*next_stop;

	count = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == 39 || s[i] == 34)
			k = s[i];
		else
			k = c;
		next_stop = ft_strchr(&s[i + 1], k);
		i += next_stop - &s[i];
		if (k != c)
			i += 2;
		count++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		wordlen;
	char	next_stop_char;
	char	*next_stop;
	char	**str;
	char	*start;

	str = malloc((count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	j = 0;
	while (s[i])
	{
		wordlen = 0;
		start = &s[i];
		if (s[i] == 39 || s[i] == 34)
		{
			start = &s[i + 1];
			next_stop_char = s[i];
			wordlen = -1;
		}
		else
			next_stop_char = c;
		next_stop = ft_strchr(&s[i + 1], next_stop_char);
		wordlen += next_stop - &s[i];
		i += wordlen;
		if (next_stop_char != c)
			i += 2;
		str[j++] = ft_substr(start, 0, wordlen);
		while (s[i] && s[i] == c)
			i++;
	}
	str[j] = NULL;
	return (str);
}

// int main(int c, char **av)
// {
// 	int i = -1;
// 	(void)av;
// 	char str[] = "ls -la";
// 	char **arr = ft_split(str, ' ');
// 	while (arr[++i])
// 			printf("%s\n", arr[i]);

// 	printf("%s\n", arr[i]);

// }