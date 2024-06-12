/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jo-tan_ft_calloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:11:38 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/28 15:08:08 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if (nmemb == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	if (size != 0 && nmemb >= SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset((int *)ptr, 0, nmemb * size);
	return (ptr);
}
