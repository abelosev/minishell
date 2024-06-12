/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:07:06 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 15:12:28 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_backslash(const char *line)
{
	char	*p;

	p = (char *)line;
	while (*p)
	{
		if (*p == '\\')
			return (0);
		p++;
	}
	return (1);
}

static int	ft_check_semicolon(const char *line)
{
	char	*p;

	p = (char *)line;
	while (*p)
	{
		if (*p == ';')
			return (0);
		p++;
	}
	return (1);
}

int	ft_valid_line(const char *line)
{
	if (!ft_check_backslash(line))
		return (ft_putstr_fd("Invalid Syntax: backslash '\\' is found\n", 2), 0);
	if (!ft_check_semicolon(line))
		return (ft_putstr_fd("Invalid Syntax: semicolon ';' is found\n", 2), 0);
	if (!ft_check_quote_pair(line))
		return (ft_putstr_fd("Invalid Syntax: quote isn't closed\n", 2), 0);
	return (1);
}
