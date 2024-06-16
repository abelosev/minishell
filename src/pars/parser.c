/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:51 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 19:51:45 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_group	*unclosed_quotes(t_group *group, t_parser *p)
{
	ft_putstr_err("Invalid syntax: unclosed quotes\n");
	invalid_group(group, 2);
	free_t_parser(p);
	return (group);
}

t_group	*group_list(t_parser *p, t_group *group, t_list_env *env)
{
	p->token_tab = ft_split1(p->line, 1);
	if (p->token_tab == NULL)
	{
		free_t_parser(p);
		return (NULL);
	}
	spaces_between_quotes(&(p->token_tab));
	p->token_list = lexer(p->token_tab);
	if (p->token_list == NULL)
	{
		free_t_parser(p);
		return (NULL);
	}
	if (syntax_pb(p->token_list))
		invalid_group(group, 2);
	else
	{
		free(group);
		group = get_group_list(p->token_list, env);
	}
	return (group);
}



t_main	*parser(char *input, t_list_env *env, int *code)
{
	t_parser	*p;
	t_main	*parsed;

	p = create_init_p();
	parsed = malloc(sizeof(t_main));
	if(!parsed)
	{
		free_t_parser(p);
		return (NULL);
	}
	parsed->group = NULL;
	parsed->hd_del = NULL;
	parsed->group = create_init_group();
	if (quotes_ok(&input) == 0)
	{
		free(parsed->hd_del);
		parsed->group = unclosed_quotes(parsed->group, p);
		return (parsed);
	}
	p->line = quotes_expand(input, env, code);
	if (p->line == NULL)
	{
		free_t_parser(p);
		if (input)
		{
			invalid_group(parsed->group, 127);
			ft_putstr_err("Command not found\n");
		}
		else
			invalid_group(parsed->group, 2);
		return (parsed);
	}
	parsed->group = group_list(p, parsed->group, env);
	parsed->hd_del = get_hd_delimiter(p->token_list);//	как обработать malloc pb ?
	free_t_parser(p);
	if (!parsed->group && !parsed->hd_del)
	{
		free(parsed);
		return (NULL);
	}
	return (parsed);
}
