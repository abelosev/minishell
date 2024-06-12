/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:22 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 15:37:02 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*enum_to_str(t_token *p)
{
	char	*type;

	if (p->type == NONE)
		type = "NONE";
	if (p->type == ARG)
		type = "ARG";
	if (p->type == PIPE)
		type = "PIPE";
	if (p->type == FILE_IN)
		type = "FILE_IN";
	if (p->type == FILE_OUT)
		type = "FILE_OUT";
	if (p->type == FILE_OUT_AP)
		type = "FILE_OUT_AP";
	if (p->type == DELIMITER)
		type = "DELIMITER";
	if (p->type == DELIMITER_Q)
		type = "DELIMITER_Q";
	return (type);
}

void	ft_print_token_lst(t_token *token_lst)
{
	t_token	*p;
	char	*type;

	p = token_lst;
	while (p)
	{
		type = enum_to_str(p);
		printf("❮%d%s/%s❯   ", p->type, type, p->word);
		p = p->next;
	}
	printf("\n");
}

void	ft_print_env_list(t_env *env)
{
	t_env	*p;
	int		i;

	i = 0;
	p = env;
	while (p)
	{
		printf("❮line: %i/%s❯\n", i + 1, p->line);
		i++;
		p = p->next;
	}
}

void	print_cmd(t_cmd **arr)
{
	while (*arr)
	{
		printf("---------CMD Table------------\n");
		ft_print_token_lst((*arr)->tokens);
		++arr;
	}
	printf("--------------------------\n");
}
