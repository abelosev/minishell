/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_find_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:45:06 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 14:45:11 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_space(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (ft_isspace(word[i]))
			return (1);
		i++;
	}
	return (0);
}

int	find_quote(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (ft_isquote(word[i]))
			return (1);
		i++;
	}
	return (0);
}

int	find_dollar(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
