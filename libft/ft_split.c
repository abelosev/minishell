/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:24:18 by aauthier          #+#    #+#             */
/*   Updated: 2024/01/01 10:56:39 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_str(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s[i])
		return (0);
	if (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			count++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c)
		count++;
	return (count);
}

int	ft_str_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

char	*ft_write_string(char const *s, char **ptr, int j, int len)
{
	int		x;
	char	*p;

	x = 0;
	p = (char *)s;
	ptr[j] = malloc((len + 1) * sizeof(char));
	if (!ptr[j])
	{
		while (j != 0)
		{
			free(ptr[j]);
			j--;
		}
		free(ptr);
		return (NULL);
	}
	while (len != 0)
	{
		ptr[j][x] = p[x];
		x++;
		len--;
	}
	ptr[j][x] = '\0';
	return (ptr[j]);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	ptr = malloc((ft_count_str(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			ptr[j] = ft_write_string(s + i, ptr, j, ft_str_len(s, c, i));
			j++;
			i += ft_str_len(s, c, i);
			if (s[i] == '\0')
				break ;
		}
		i++;
	}
	ptr[j] = NULL;
	return (ptr);
}
