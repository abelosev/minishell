/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:51:23 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 14:43:04 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expansion_sign(char *word)
{
	char	*p;

	p = word;
	while (*p)
	{
		if (*p == '$')
			return (1);
		p++;
	}
	return (0);
}

static int	skip_quote(char *p)
{
	int	len;
	int	inquote;

	len = 0;
	while (p[len] != '$' && p[len])
	{
		if (ft_isquote(p[len]))
		{
			inquote = 1;
			while (p[len + inquote] != p[len])
				inquote++;
			len += inquote;
		}
		len++;
	}
	return (len);
}

int	ft_count_parsing_len(char *word)
{
	char	*p;
	int		len;

	p = word;
	len = 0;
	if (p[len] == '$' && (p[len + 1] == '$' || p[len + 1] == '?'))
		return (2);
	if (p[len] == '$' && (ft_isspace(p[len + 1])
			|| !p[len + 1] || !ft_isenvname(p[len + 1])))
		return (1);
	if (p[len] == '$' && ft_isenvname(p[len + 1]))
	{
		len++;
		if (ft_isdigit(p[len]))
			return (2);
		while (ft_isenvname(word[len]) && p[len] && p[len] != '$')
			len++;
	}
	else
	{
		len = skip_quote(p);
	}
	return (len);
}

t_token	*ft_divide_arg_env(char *str)
{
	int		word_len;
	char	*word;
	t_token	*new;
	t_token	*head;

	new = NULL;
	head = NULL;
	while (*str)
	{
		if (*str == '$' && ft_isquote(*(str + 1)))
			str++;
		word_len = ft_count_parsing_len(str);
		word = malloc(word_len + 1);
		if (!word)
			return (NULL);
		ft_strlcpy(word, str, word_len + 1);
		new = ft_newtoken(word);
		if (head == NULL)
			head = new;
		else
			ft_addtoken(head, new);
		str += word_len;
	}
	return (head);
}
