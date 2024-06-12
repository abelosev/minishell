/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:38 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 13:32:30 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_combine(t_token *lst)
{
	char	*ret;
	char	*tmp;
	t_token	*p;

	ret = malloc(1);
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	p = lst;
	while (p)
	{
		if (p->word != NULL)
		{
			tmp = ft_strjoin(ret, p->word);
			free(ret);
			ret = tmp;
		}
		p = p->next;
	}
	return (ret);
}

void	clear_quote(char **string, t_env *env, int exit_code, t_mini *mini)
{
	t_token	*pre;
	char	*new;

	pre = ft_break_string(*string);
	ft_parsing(mini, pre);
	ft_process_quote(pre, env, exit_code);
	new = ft_combine(pre);
	ft_token_free_lst(pre);
	free(*string);
	*string = new;
}

void	ft_parsing(t_mini *mini, t_token *lst)
{
	t_token	*p;

	p = lst;
	while (p)
	{
		if (p->type == NONE && ft_check_quote_pair(p->word) == 3)
			expansion(&(p->word), mini->env, mini->exit_code);
		else if (p->type != NONE && ft_check_quote_pair(p->word) == 3)
			expansion(&(p->word), mini->env, mini->exit_code);
		else if (p->type != NONE && ft_check_quote_pair(p->word) != 3)
			clear_quote(&(p->word), mini->env, mini->exit_code, mini);
		p = p->next;
	}
}
