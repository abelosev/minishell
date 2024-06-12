/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:12:23 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/13 18:12:25 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	c2;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	c2 = (unsigned char)c;
	while (i < n)
	{
		if (*(ptr + i) == c2)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
