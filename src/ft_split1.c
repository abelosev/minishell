/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:13 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/15 21:39:07 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	ft_is_delimiter1(char c, int flag)
{
	if (flag == 1)
		return (c == ' ' || c == '\t');
	else if (flag == 2)
		return (c == ':');
	else if (flag == 3)
		return (c == 28);
	else
		return (0);
}

int	ft_words_len1(char *str, int flag)
{
	int	idx;
	int	length;

	idx = 0;
	length = 0;
	while (str[idx] != '\0')
	{
		if (!ft_is_delimiter1(str[idx], flag))
		{
			length++;
			idx++;
		}
		else
			idx++;
	}
	return (length);
}

char	*ft_get_word1(char *str, int flag)
{
	int			idx;
	char		*word;

	idx = 0;
	while (str[idx] != '\0' && !ft_is_delimiter1(str[idx], flag))
		idx++;
	word = (char *)malloc(sizeof(char) * (idx + 1));
	if (!word)
		return (NULL);
	idx = 0;
	while (str[idx] != '\0' && !ft_is_delimiter1(str[idx], flag))
	{
		word[idx] = str[idx];
		idx++;
	}
	word[idx] = '\0';
	return (word);
}

char	**ft_split1(char *str, int flag)
{
	int		idx;
	char	**split;

	idx = 0;
	split = (char **)malloc(sizeof(char *) * (ft_words_len1(str, flag) + 1));
	if (!split)
		return (NULL);
	while (*str)
	{
		while (*str && ft_is_delimiter1(*str, flag))
			str++;
		if (*str && !ft_is_delimiter1(*str, flag))
		{
			split[idx] = ft_get_word1(str, flag);
			idx++;
		}
		while (*str && !ft_is_delimiter1(*str, flag))
			str++;
	}
	split[idx] = NULL;
	return (split);
}
