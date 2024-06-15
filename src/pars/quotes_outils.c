/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 23:10:48 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/15 21:18:57 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_meta(char *str)
{
	return (*str == '|' || *str == '<' || *str == '>');
}

int	is_meta_move(char **str)
{
	if (is_meta(*str) > 0)
	{
		if ((**str == '>' || **str == '<')
			&& *(*str + 1) && (**str == *(*str + 1)))
			(*str)++;
		(*str)++;
		return (1);
	}
	return (0);
}

int	ending_quotes_nb(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 31)
			len++;
		i++;
	}
	return (len);
}

char	*with_28(char **str)
{
	int		i;
	int		len;
	int		l;
	char	*new;

	i = 0;
	len = 0;
	l = ft_strlen(*str) + ending_quotes_nb(*str) + 1;
	new = malloc(sizeof(char) * l);
	if (!new)
		return (NULL);
	while (i + 1 < l && (*str)[len])
	{
		new[i] = (*str)[len];
		i++;
		if ((*str)[len] == 31 && i < l)
		{
			new[i] = 28;
			i++;
		}
		len++;
	}
	new[i] = '\0';
	return (new);
}

int	spaces_nb(char *str)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		if (is_meta_move(&str) > 0)
			counter++;
		else
			str++;
	}
	return (counter * 2);
}
