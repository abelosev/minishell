/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:24:14 by aauthier          #+#    #+#             */
/*   Updated: 2023/11/28 15:24:28 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_char;
	unsigned char	*src_char;

	i = 0;
	dst_char = (unsigned char *)dest;
	src_char = (unsigned char *)src;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (i < n)
	{
		dst_char[i] = src_char[i];
		i++;
	}
	return (dst_char);
}
