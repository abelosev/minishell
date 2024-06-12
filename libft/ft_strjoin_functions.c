/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:10:37 by aauthier          #+#    #+#             */
/*   Updated: 2023/11/28 15:31:57 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	str_size;
	char	*result;

	str_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = malloc(sizeof(char) * str_size);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	return (result);
}

char	*ft_strnjoin_wsep(char const *s1, char const *s2, size_t ns2, char *sep)
{
	size_t	str_size;
	char	*result;

	result = NULL;
	str_size = ft_strlen(s1) + ns2 + ft_strlen(sep) + 1;
	result = ft_calloc(sizeof(char), str_size);
	if (!result)
		return (NULL);
	ft_strncpy(result, s2, ns2);
	ft_strcat(result, sep);
	ft_strcat(result, s1);
	return (result);
}
