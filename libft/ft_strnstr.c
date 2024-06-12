/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:14:59 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/13 18:15:07 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_len;

	i = 0;
	l_len = ft_strlen(little);
	if (l_len == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (i < len && big[i])
	{
		if (big[i] == little[0] && (i + l_len) > len)
			break ;
		else if (big[i] == little[0] && ft_strncmp(big + i, little, l_len) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
