/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:14:48 by aauthier          #+#    #+#             */
/*   Updated: 2023/11/28 13:15:30 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	pos;

	i = 0;
	pos = ft_strlen(dest);
	while (src[i])
	{
		dest[pos] = src[i];
		pos++;
		i++;
	}
	dest[pos] = '\0';
	return (dest);
}
