/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:18:19 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/13 18:18:26 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_sep(char const c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_findstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_is_sep(s1[i], set) == 1)
			i++;
		else
			break ;
	}
	return (i);
}

int	ft_trimlen(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1)
	{
		if (ft_is_sep(s1[start], set) == 1)
			start++;
		else
			break ;
	}
	while (end > 0)
	{
		if (ft_is_sep(s1[end], set) == 1)
			end--;
		else
			break ;
	}
	if (end - start < 0)
		return (0);
	return (end - start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	int		i;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = ft_findstart(s1, set);
	len = ft_trimlen(s1, set);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (len != 0)
	{
		ptr[i] = s1[start];
		i++;
		start++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}
