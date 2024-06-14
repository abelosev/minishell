/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:27:03 by abelosev          #+#    #+#             */
/*   Updated: 2021/04/08 12:30:32 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst1;
	char	*src1;

	dst1 = (char*)dst;
	src1 = (char*)src;
	if (dst1 == src1)
		return (dst1);
	if (src1 < dst1)
	{
		while (len-- > 0)
		{
			dst1[len] = src1[len];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			dst1[i] = src1[i];
			i++;
		}
	}
	return (dst);
}
