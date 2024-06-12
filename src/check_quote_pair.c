/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_pair.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:15:41 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 15:15:51 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_quote_type(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

static char	*check_quote_ext(char *p, int *quote, int *quote_type)
{
	int	inquote_len;

	inquote_len = 1;
	if (ft_isquote(*p))
	{
		*quote = 1;
		*quote_type = ft_quote_type(*p);
		while ((*(p + inquote_len)) != '\0')
		{
			if ((*(p + inquote_len)) == *p)
			{
				*quote = 0;
				p += inquote_len;
				break ;
			}
			inquote_len++;
		}
		if (*quote != 0)
		{
			*quote_type = 0;
			return (p + inquote_len);
		}
	}
	return (p + 1);
}

int	ft_check_quote_pair(const char *string)
{
	int		quote;
	int		quote_type;
	char	*p;

	quote = 0;
	quote_type = 3;
	p = (char *)string;
	while (*p)
	{
		p = check_quote_ext(p, &quote, &quote_type);
	}
	return (quote_type);
}
