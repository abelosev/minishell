/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:09:37 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/14 04:29:56 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	is_special(char c)
{
	return (!ft_isdigit(c) && !ft_isalpha(c) && c != '*' && c != '#' && c != '?');
}

int	delimiter_nb(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || (is_special(str[i])) || str[i] == 30)
			nb += 2;
		if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
			nb++;
		i++;
	}
	return (nb);
}

t_tokenizer	*init_data(char *s)
{
	t_tokenizer	*d;

	d = malloc(sizeof(t_tokenizer));
	if (!d)
		return (NULL);
	d->i = 0;
	d->k = 0;
	d->len = delimiter_nb(s) + ft_strlen(s) + 1;
	d->new = malloc(sizeof(char) * d->len);
	if (!d->new)
		return (NULL);
	return (d);
}

void	between_single(t_tokenizer *d, char *s)
{
	d->new[d->k] = 28;
	d->k++;
	while (s[d->i] && s[d->i] != 31 && d->k < d->len)
	{
		d->new[d->k] = s[d->i];
		d->k++;
		d->i++;
	}
	if (d->k < d->len && s[d->i] && s[d->i] == 31)
	{
		d->new[d->k] = 31;
		d->k++;
		d->i++;
	}
}

void	before_expand_or_special(t_tokenizer *d, char *s)
{
	d->new[d->k] = 28;
	d->new[d->k + 1] = s[d->i];
	d->k += 2;
	d->i++;
}
