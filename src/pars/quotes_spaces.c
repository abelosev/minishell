/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 23:04:54 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 02:28:53 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	hide_spaces_between_quotes(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == 29 || (*str)[i] == 30)
		{
			while ((*str)[i] && (*str)[i] != 31)
			{
				if ((*str)[i] == ' ' || (*str)[i] == '\t')
					(*str)[i] = 27;
				i++;
			}
		}
		if ((*str)[i])
			i++;
	}
}

void	quotes_started(char **new_str, char **str, int *len, int *i)
{
	while (**str && **str != 31 && *i < *len)
	{
		(*new_str)[*i] = **str;
		(*str)++;
		(*i)++;
	}
	if (**str && *i < *len)
	{
		(*new_str)[*i] = **str;
		(*str)++;
		(*i)++;
	}
}

void	meta_detected(char **new_str, char **str, int *len, int *i)
{
	(*new_str)[*i] = ' ';
	(*new_str)[(*i) + 1] = **str;
	if (**str != '|' && (**str == *((*str) + 1)))
	{
		(*new_str)[(*i) + 2] = *((*str) + 1);
		(*str)++;
		if ((*i) + 3 < *len)
			(*i)++;
	}
	(*str)++;
	(*new_str)[(*i) + 2] = ' ';
	(*i) += 3;
	if (**str == 29 || **str == 30)
		quotes_started(new_str, str, len, i);
}

void	get_new_string(char **new_str, char *str, int len, int i)
{
	while (i < len && *str)
	{
		if (*str == 29 || *str == 30)
			quotes_started(new_str, &str, &len, &i);
		if (*str && (is_meta(str) > 0) && (i + 2 < len))
			meta_detected(new_str, &str, &len, &i);
		(*new_str)[i] = *str;
		if (i < len)
			i++;
		if (*str)
			(str)++;
	}
	(*new_str)[i] = '\0';
}

char	*add_spaces(char **tmp)
{
	char	*new_str;
	char	*str;
	char	*start;
	int		len;
	int		i;

	i = 0;
	str = with_28(tmp);
	start = str;
	hide_spaces_between_quotes(&str);
	len = spaces_nb(str) + ft_strlen(str) + 1;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	get_new_string(&new_str, str, len, i);
	free(start);
	return (new_str);
}
