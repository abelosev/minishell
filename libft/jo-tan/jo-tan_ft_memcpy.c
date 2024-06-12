/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jo-tan_ft_memcpy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:15:59 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/28 15:08:09 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
		*(unsigned char *)(dest + i++) = *(unsigned char *)(src++);
	return (dest);
}
