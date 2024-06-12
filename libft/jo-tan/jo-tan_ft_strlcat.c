/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jo-tan_ft_strlcat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:21:19 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/28 15:08:06 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	end;

	if (size == 0 && (!src || !dst))
		return (0);
	dst_len = ft_strlen((const char *)dst);
	src_len = ft_strlen(src);
	i = 0;
	end = dst_len;
	if (size == 0)
		return (src_len);
	if (size < dst_len)
		return (src_len + size);
	else
	{
		while (src[i] && (dst_len + i) < size)
			dst[end++] = src[i++];
		if ((dst_len + i) == size && dst_len < size)
			dst[--end] = '\0';
		else
			dst[end] = '\0';
		return (dst_len + src_len);
	}
}
