/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 10:16:53 by abelosev          #+#    #+#             */
/*   Updated: 2021/04/30 11:04:57 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_counting_strings(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nb++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb);
}

char	*ft_create_string(const char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		x;
	int		y;
	int		number;
	char	**array;

	if (!s)
		return (NULL);
	number = ft_counting_strings(s, c);
	if (!(array = (char**)malloc(sizeof(char *) * (number + 1))))
		return (NULL);
	x = 0;
	y = 0;
	while (s[x])
	{
		while (s[x] && s[x] == c)
			x++;
		if (s[x] && s[x] != c)
		{
			array[y++] = ft_create_string(&s[x], c);
			while (s[x] && s[x] != c)
				x++;
		}
	}
	array[y] = NULL;
	return (array);
}
