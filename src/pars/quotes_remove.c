/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 23:17:10 by abelosev          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/15 21:29:49 by abelosev         ###   ########.fr       */
=======
/*   Updated: 2024/06/15 21:18:57 by aauthier         ###   ########.fr       */
>>>>>>> refs/remotes/origin/master
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	quotes_nb(char *str, char c)
{
	int	nb;

	nb = 0;
	while (*str)
	{
		if (*str == c)
			nb++;
		str++;
	}
	return (nb * 2);
}

void	quotes_removing(char *str, char c, char **new, t_remove *r)
{
	while (str[r->i] && r->k < r->len)
	{
		if (str[r->i] == c)
		{
			(r->i)++;
			while (str[r->i] && str[r->i] != 31 && r->k < r->len)
			{
				(*new)[r->k] = str[r->i];
				(r->k)++;
				(r->i)++;
			}
			if (str[r->i] && str[r->i] == 31)
				(r->i)++;
		}
		if (str[r->i] && str[r->i] != c && r->k < r->len)
		{
			(*new)[r->k] = str[r->i];
			(r->k)++;
			(r->i)++;
		}
		else
			continue ;
	}
	(*new)[r->k] = '\0';
}

char	*no_quotes(char *str, char c)
{
	char		*new;
	t_remove	*r;

	r = malloc(sizeof(t_remove));
	if (!r)
		return (NULL);
	r->i = 0;
	r->k = 0;
	r->len = ft_strlen(str) - quotes_nb(str, c) + 1;
	new = malloc(sizeof(char) * r->len);
	if (!new)
		return (NULL);
	quotes_removing(str, c, &new, r);
	if (r)
		free(r);
	return (new);
}
