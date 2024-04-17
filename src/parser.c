/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:51 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/16 23:15:29 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void invalid_group(t_group *group, int flag)
{
	group->flag_fail = flag;
	group->cmd = NULL;
	group->redir_in = NULL;
	group->redir_out = NULL;
	group->app_out = NULL;
	group->app_in = NULL;
	group->next = NULL;
}

int is_folder(char *line)
{
	int fd;
	DIR *d;
	int res;

	fd = open(line, O_WRONLY);
	d = opendir(line);
	if(fd == -1 && d != NULL)
	{
		ft_putstr_err("minishell: ");
		ft_putstr_err(line);
		ft_putstr_err(": Is a directory\n");
		res = 1;
	}
	else
		res = 0;
	if(fd > 0)
		close(fd);
	if(d)
		closedir(d);
	return (res);
}

void init_t_parser(t_parser *p)
{
	p->line = NULL;
	p->token_tab = NULL;
	p->token_list = NULL;
}

t_parser *create_init_p (void)
{	
	t_parser *p;
	
	p = malloc(sizeof(t_parser));
	if(!p)
		return (NULL);
	init_t_parser(p);
	return (p);
}

t_group *create_init_group(void)
{
	t_group *group;
	
	group = malloc(sizeof(t_group));
	if(!group || group == NULL) //to remove "group == NULL" ?
		return (NULL);
	invalid_group(group, 0);
	return (group);
}

int pre_check(char *input, t_group *group)
{
	if(only_spaces(input))
	{
		invalid_group(group, 2);
		return (1);
	}
	if(is_folder(input))
	{
		invalid_group(group, 126);
		return (1);
	}
	return (0);
}

t_group *parser(char *input, t_list_env *env)
{
	t_parser *p;
	t_group *group;

	p = create_init_p();
	group = create_init_group();

	// if(only_spaces(input))
	// {
	// 	invalid_group(group, 2);
	// 	return (group);
	// }
	// if(is_folder(input))
	// {
	// 	invalid_group(group, 126);
	// 	return (group);
	// }

	if(pre_check(input, group))
	{
		free_t_parser(p);
		return (group);
	}

	p->line = quotes_expand(input, env);
	if(p->line == NULL)
	{
		invalid_group(group, 2); //malloc pb or unclosed quotes
		return (group);
	}
	p->token_tab = ft_split1(p->line, 1);
	if(p->token_tab == NULL)
	{
		free_t_parser(p);
		return (NULL); //malloc pb
	}
	
	p->token_list = lexer(p->token_tab);
	if(p->token_list == NULL)
	{
		free_t_parser(p);
		return (NULL); //malloc pb	
	}

	if(syntax_pb(p->token_list)) //may it cause pb for some syntax pb (?)
	{
		free_t_parser(p);
		invalid_group(group, 2);
		return (group);
	}
	else
	{
		free(group);
		group = get_group_list(p->token_list, env);
	}
	free_t_parser(p);
	return (group);
}

// printf("no quotes + expand: %s\n", p->line);

// printf("Token list:\n");
// print_token_list(p->token_list);
// printf("\n");