/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:55:10 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 15:22:06 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (ft_isspace(*str))
		++str;
	return (str);
}

int	end_of_cmd(int c)
{
	if (c == 0 || c == '#' || c == ':')
		return (1);
	if (c == '!')
		return (2);
	else
		return (0);
}

//Here i have the char ':' and '!' which need to be treated like '#'
// Except '!' has an exit code of 1