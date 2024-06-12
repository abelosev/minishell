/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:27:24 by aauthier          #+#    #+#             */
/*   Updated: 2023/11/28 15:27:42 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s_char;

	i = -1;
	s_char = (char *)s;
	if (c == '\0')
		return (&s_char[ft_strlen(s)]);
	while (s_char[++i])
		if (s_char[i] == (char)c)
			return (&s_char[i]);
	return (NULL);
}
