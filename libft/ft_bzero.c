/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:51:53 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 02:04:13 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	i = 0;
	if (n == 0)
		return ;
	s1 = (unsigned char *)s;
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
}
