/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:58:42 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 14:59:54 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_type(t_token *p)
{
	if (p->word[0] == '\0')
		p->type = ARG;
	else if (ft_strncmp(p->word, "|", ft_strlen(p->word)) == 0)
		p->type = PIPE;
	else if (ft_strncmp(p->word, "<", ft_strlen(p->word)) == 0)
		p->type = FILE_IN;
	else if (ft_strncmp(p->word, "<<", ft_strlen(p->word)) == 0)
	{
		if (p->next != NULL && find_quote(p->next->word))
			p->type = DELIMITER_Q;
		else
			p->type = DELIMITER;
	}
	else if (ft_strncmp(p->word, ">", ft_strlen(p->word)) == 0)
		p->type = FILE_OUT;
	else if (ft_strncmp(p->word, ">>", ft_strlen(p->word)) == 0)
		p->type = FILE_OUT_AP;
	else
		p->type = ARG;
}

void	ft_update_token_type(t_token *lst)
{
	t_token	*p;

	if (!lst)
		return ;
	p = lst;
	while (p)
	{
		if (p->type == NONE)
		{
			assign_type(p);
		}
		p = p->next;
	}
}
