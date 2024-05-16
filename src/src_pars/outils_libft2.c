/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_libft2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:23:10 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/16 14:03:14 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	is_digit(char c)
{
	return (c >= '1' && c <= '9');
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		res[i + k] = s2[k];
		k++;
	}
	res[i + k] = '\0';
	return (res);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	k;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	res = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		res[i + k] = s2[k];
		k++;
	}
	res[i + k] = '\0';
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	char	c1;
	size_t	i;

	c1 = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c1)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c1)
		return ((char *)(s + i));
	return (NULL);
}
