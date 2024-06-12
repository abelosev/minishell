/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:11:20 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/13 18:11:23 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		i;
	size_t		len;
	char		*res;

	if (!s || !f)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (++i < len)
		res[i] = f(i, s[i]);
	res[i] = '\0';
	return (res);
}
