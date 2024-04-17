/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:33:24 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/15 21:35:04 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	is_digit(char c)
{
	return (c >= '1' && c <= '9');
}

char	**copy_tab(char **tab)
{
	int		nb_line;
	int		i;
	char	**copy;

	nb_line = 0;
	i = 0;
	while (tab[nb_line])
		nb_line++;
	copy = malloc(sizeof(char **) * (nb_line));
	while (i < nb_line && tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
