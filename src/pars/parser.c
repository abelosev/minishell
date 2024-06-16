/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:51 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 20:34:46 by abelosev         ###   ########.fr       */
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

t_main	*line_null(char *input, t_parser *p, t_main *m)
{
	free_t_parser(p);
	if (input)
	{
		invalid_group(m->group, 127);
		ft_putstr_err("Command not found\n");
	}
	else
		invalid_group(m->group, 2);
	return (m);
}

t_main	*parser(char *input, t_list_env *env, int *code)
{
	t_parser	*p;
	t_main		*m;

	p = create_init_p();
	m = create_init_m(p);
	if (!p || !m)
		return (NULL);
	if (quotes_ok(&input) == 0)
	{
		m->group = unclosed_quotes(m->group, p);
		return (m);
	}
	p->line = quotes_expand(input, env, code);
	if (p->line == NULL)
		return (line_null(input, p, m));
	m->group = group_list(p, m->group, env);
	m->hd_del = get_hd_delimiter(p->token_list);
	free_t_parser(p);
	if (!m->group && !m->hd_del)
		return (free(m), NULL);
	return (m);
}
