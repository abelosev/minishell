/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_expand_tokenizer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:12:56 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/16 21:01:39 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

int is_special(char c)
{
	return (!is_digit(c) && !is_alpha(c) && c != '*' && c != '#' && c != '?'); //?? remove this : c != '*' && c != '#'
}

int delimiter_nb(char *str)
{
	int nb;
	int i;

	nb = 0;
	i = 0;

	while(str[i])
	{
		if(str[i] == '$' || (is_special(str[i])) || str[i] == 30) //we dont use all this memory => potential leak
			nb++;
		if(str[i] == '$' && str[i + 1] && is_digit(str[i + 1]))
			nb++;
		i++;
	}
	return (nb);
}

char *temp_tokenizer(char *str)
{
	int len;
	int i;
	int k;
	char *new;

	i = 0;
	k = 0;
	len = delimiter_nb(str) + ft_strlen(str) + 1;
	new = malloc(sizeof(char) * len);
	if(!new)
		return (NULL);
	while(k < len && str[i])
	{
		if(str[i] == '$' && str[i + 1] && (str[i + 1] == 30 || str[i + 1] == 29))
			i++;
		if(str[i] && str[i] == 30) //избыточное str[i] ???
		{
			new[k] = 28;
			k++;
			while(str[i] && str[i] != 31 && k < len)
			{
				new[k] = str[i];
				i++;
				k++;
			}
			if(k < len && str[i])
			{
				new[k] = 30;
				k++;
				i++;
			}
		}
		else if(str[i] && (str[i] == '$' || is_special(str[i])) && (k + 1 < len))
		{
			new[k] = 28;
			new[k + 1] = str[i];
			k += 2;
			i++;
		}
		else if(i > 0 && str[i - 1] && str[i] && str[i - 1]== '$' && is_digit(str[i]) && (k + 1 < len))
		{
			new[k] = str[i];
			new[k + 1] = 28;
			k += 2;
			i++;
		}
		else if(i > 0 && str[i - 1] && str[i - 1] == 31 && str[i] && (k + 1 < len))
		{
			new[k] = 28;
			new[k + 1] = str[i];
			k += 2;
			i++;
		}
		else
		{
			new[k] = str[i];
			k++;
			i++;
		}
	}
	new[k] = '\0';
	return (new);
}
