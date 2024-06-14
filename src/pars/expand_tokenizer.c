/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:12:56 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/14 04:29:56 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	after_digit(t_tokenizer *d, char *s)
{
	d->new[d->k] = s[d->i];
	d->new[d->k + 1] = 28;
	d->k += 2;
	d->i++;
}

void	ending_quote(t_tokenizer *d, char *s)
{
	d->new[d->k] = 28;
	d->new[d->k + 1] = s[d->i];
	d->k += 2;
	d->i++;
}

void	par_defaut(t_tokenizer *d, char *s)
{
	d->new[d->k] = s[d->i];
	d->k++;
	d->i++;
}

void	temp_token_outil(t_tokenizer *d, char *str)
{
	if (str[d->i] == 30)
		between_single(d, str);
	else if (str[d->i] && (str[d->i] == '$' || is_special(str[d->i]))
		&& (d->k + 1 < d->len))
		before_expand_or_special(d, str);
	else if (d->i > 0 && str[d->i - 1] && str[d->i] && str[d->i - 1] == '$'
		&& ft_isdigit(str[d->i]) && (d->k + 1 < d->len))
		after_digit(d, str);
	else if (d->i > 0 && str[d->i - 1] && str[d->i - 1] == 31
		&& str[d->i] && (d->k + 1 < d->len))
		ending_quote(d, str);
	else
		par_defaut(d, str);
}

char	*temp_tokenizer(char *str)
{
	char		*res;
	t_tokenizer	*d;

	d = init_data(str);
	while (d->k < d->len && str[d->i])
	{
		if (str[d->i] == '$' && str[d->i + 1]
			&& (str[d->i + 1] == 30 || str[d->i + 1] == 29))
			d->i++;
		temp_token_outil(d, str);
	}
	d->new[d->k] = '\0';
	res = d->new;
	free(d);
	return (res);
}
