/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_free_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 02:43:43 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 19:05:49 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	free_group_list(t_group *group)
{
	t_group	*tmp;

	while (group != NULL)
	{
		tmp = group->next;
		if (group->cmd)
			free_tab(group->cmd);
		if (group->app_out)
			free(group->app_out);
		if (group->redir_in)
			free(group->redir_in);
		if (group->redir_out)
			free(group->redir_out);
		free(group);
		group = tmp;
	}
}

void	free_t_parser(t_parser *p)
{
	if (p->line)
		free(p->line);
	if (p->token_tab)
		free_tab(p->token_tab);
	if (p->token_list)
		free_tokens(p->token_list);
	if (p)
		free(p);
}

void	free_main(t_main *parsed)
{
	if (!parsed)
		return ;
	else
	{
		if (parsed->group)
			free_group_list(parsed->group);
		free(parsed);
		//free(code); 				no need (?)
	}
}
