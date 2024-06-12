/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:59:57 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 12:05:52 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Receives prev & non-NULL token
// Frees current token
// If prev exists, links prev token to next token
// Returns next token
t_token	*remove_current_token(t_token *prev, t_token *token)
{
	t_token	*next;

	next = token->next;
	if (prev)
		prev->next = next;
	return (free_single_token(token), next);
}

t_token	*split_process(t_token *tokens,
	t_cmd **simple_cmds, t_token **prev, int *type)
{
	t_cmd	*new_cmd;

	while (tokens->type > ARG)
	{
		if (tokens->type > PIPE)
			*type = tokens->type;
		tokens = remove_current_token(NULL, tokens);
	}
	new_cmd = ft_lstnew_cmd(tokens);
	ft_lstadd_back_cmd(simple_cmds, new_cmd);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type > PIPE)
		{
			*type = tokens->type;
			tokens = remove_current_token(*prev, tokens);
		}
		*prev = tokens;
		(*prev)->type = *type;
		*type = 1;
		tokens = tokens->next;
	}
	if (*prev)
	(*prev)->next = NULL;
	return (tokens);
}

t_cmd	*split_into_simplecmds(t_token *tokens)
{
	t_cmd	*simple_cmds;
	t_token	*prev;
	int		type;

	prev = NULL;
	simple_cmds = NULL;
	type = 1;
	while (tokens)
	{
		tokens = split_process(tokens, &simple_cmds, &prev, &type);
	}
	return (simple_cmds);
}

t_cmd	**lst_to_arr(t_cmd *lst)
{
	t_cmd	**arr;
	int		size;
	int		i;

	size = ft_lstsize_cmd(lst);
	arr = malloc ((size + 1) * sizeof(*arr));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		arr[i] = lst;
		++i;
		lst = lst->next;
	}
	arr[i] = 0;
	return (arr);
}

t_cmd	**create_cmd_arr(t_token *tokens)
{
	t_cmd	**arr;
	t_cmd	*simple_cmds;

	simple_cmds = split_into_simplecmds(tokens);
	if (!simple_cmds)
		return (NULL);
	arr = lst_to_arr(simple_cmds);
	if (!arr)
		return (NULL);
	return (arr);
}
