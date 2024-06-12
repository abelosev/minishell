/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:38 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 13:41:53 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_quote_len(char *string)
{
	int	len;

	len = 0;
	if (ft_isquote(string[len]))
	{
		len = 1;
		while (string[len] != string[0])
			len++;
		len++;
	}
	else
	{
		len = 0;
		while (string[len] && !ft_isquote(string[len]))
			len++;
	}
	return (len);
}

t_token	*ft_break_string(char *string)
{
	int		word_len;
	char	*word;
	t_token	*new;
	t_token	*head;

	new = NULL;
	head = new;
	while (*string)
	{
		word_len = ft_count_quote_len(string);
		word = malloc(word_len + 1);
		if (!word)
			return (NULL);
		ft_strlcpy(word, string, word_len + 1);
		new = ft_newtoken(word);
		if (head == NULL)
			head = new;
		else
			ft_addtoken(head, new);
		string += word_len;
	}
	return (head);
}

void	process_quote(char **word)
{
	char	*clean;
	int		len;
	int		i;
	int		j;

	i = 1;
	j = 0;
	len = ft_strlen(*word);
	clean = malloc(len - 1);
	if (!clean)
		return ;
	while (i < len - 1)
	{
		clean[j] = (*word)[i];
		j++;
		i++;
	}
	clean[j] = '\0';
	free(*word);
	*word = clean;
}

void	process_double(char **word, t_env *env, int exit_code)
{
	process_quote(word);
	hd_expansion(word, env, exit_code);
}

void	ft_process_quote(t_token *lst, t_env *env, int exit_code)
{
	t_token	*p;

	p = lst;
	while (p)
	{
		if ((p->word[0]) == '\'')
			process_quote(&(p->word));
		else if ((p->word[0]) == '\"')
			process_double(&(p->word), env, exit_code);
		p = p->next;
	}
}
