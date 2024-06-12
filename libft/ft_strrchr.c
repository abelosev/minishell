/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:16:46 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/13 18:16:47 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int)ft_strlen(s);
	if (s[len] == (char) c)
		return ((char *)(s + len));
	while (len != -1)
	{
		if (s[len] == (char) c)
			return ((char *)(s + len));
		len--;
	}
	return (NULL);
}
