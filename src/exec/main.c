/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:08:39 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/26 18:29:14 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	g_status = 0;

void	exit_minishell(t_list_env *env, char *line, t_main *p, int code)
{
	if (env)
		free_envp_list(env);
	if (p)
		free_main(p);
	if (line)
		free(line);
	clear_history();
	exit(code);
}

void	end_minishell_loop(t_main *p, t_list_env *env)
{
	if (p)
		free_main(p);
	if (env)
		free_envp_list(env);
	clear_history();
}

void	update_code(int *code)
{
	if (g_status)
		*code = g_status + 128;
}

void	minishell_loop(t_list_env *env, int *code)
{
	char		*line;
	t_main		*parsed;

	while (1)
	{
		parent_signal();
		g_status = 0;
		line = readline(">$ ");
		update_code(code);
		if (!line)
			line_p_null(env, code);
		if (check_line(line, code))
			continue ;
		add_history(line);
		parsed = parser(line, env, code);
		if (!parsed)
			exit_minishell(env, line, parsed, *code);
		if (check_group(parsed, line, code))
			continue ;
		if (line)
			free(line);
		*code = ft_exec(parsed, env, code);
		update_code(code);
	}
	end_minishell_loop(parsed, env);
}

int	main(int argc, char **argv, char **envp)
{
	t_list_env	*new_env;
	int			code;

	g_status = 0;
	if (!argv || argc != 1)
		return (1);
	if (!envp || !envp[0])
		new_env = get_mini_env();
	else
		new_env = get_list(envp);
	if (!new_env)
		return (perror("new_env"), 1);
	code = 0;
	minishell_loop(new_env, &code);
	parent_signal();
	if (new_env)
		free_envp_list(new_env);
	if (g_status)
		code = g_status + 128;
	return (code);
}
