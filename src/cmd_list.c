/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:27:55 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 10:30:07 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_token_free_lst(cmd->tokens);
	free(cmd);
}

t_cmd	*ft_lstnew_cmd(t_token *tokens)
{
	t_cmd	*strct;

	strct = calloc(1, sizeof(*strct));
	if (!strct)
		return (NULL);
	strct->tokens = tokens;
	return (strct);
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	t_cmd	*strct;

	if (!lst)
		return (NULL);
	strct = lst;
	while (strct->next)
	{
		strct = strct->next;
	}
	return (strct);
}
