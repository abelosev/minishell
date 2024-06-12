/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:32:50 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/04 21:28:41 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_parsing_len_hd(char *word)
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
		while (p[len] != '$' && p[len])
			len++;
	}
	return (len);
}

t_token	*ft_divide_arg_env_hd(char *string)
{
	int		word_len;
	char	*word;
	t_token	*new;
	t_token	*head;

	new = NULL;
	head = new;
	while (*string)
	{
		word_len = ft_count_parsing_len_hd(string);
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

void	hd_expansion(char **word, t_env *env, int exit_code)
{
	t_token	*pre;
	char	*new;

	if (check_expansion_sign(*word) == 0)
		return ;
	pre = ft_divide_arg_env_hd(*word);
	ft_process_env(pre, env, exit_code);
	new = ft_combine(pre);
	ft_token_free_lst(pre);
	free(*word);
	*word = new;
}

char	*ft_heredoc_expand(
	char *str, enum e_type type, t_env *env, int old_exit)
{
	if (type == DELIMITER_Q || !find_dollar(str))
		return (str);
	hd_expansion(&str, env, old_exit);
	if (!str)
		return (perror("heredoc : reconstruct word "), NULL);
	return (str);
}
