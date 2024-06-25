/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 03:14:34 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/25 14:02:31 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	exit_minishell(t_list_env *env, char *line, t_main *p, int code)
{
	if(env)
		free_envp_list(env);
	if (p)
		free_main(p);
	if (line)
		free(line);
	clear_history();
	exit(code);
}

int	end_minishell_loop(t_main *p, t_list_env *env)
{
	if (p)
		free_main(p);
	if(env)
		free_envp_list(env);
	clear_history();
}

void	minishell_loop(t_list_env *env, int *code)
{
	char		*line;
	t_main		*parsed;

	parent_signal();
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		g_status = 0;
		line = get_line(">$ ");
		if (!line)
			exit_minishell(env, line, NULL, 1);
		if (check_line(line, code))
			continue ;
		add_history(line);
		parsed = parser(line, env, code);
		if (!parsed)
			exit_minishell(env, line, parsed, 1);
		if (check_group(parsed, line, code))
			continue ;
		if (line)
			free(line);
		*code = ft_exec(parsed, env, code);
	}
	end_minishell_loop(parsed, env);
	if (g_status != 0)			//???
		*code = g_status;
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
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	minishell_loop(new_env, &code);
	if(new_env)
		free_envp_list(new_env);
	if (g_status != 0) //to make sure
		code = g_status;
	return (code);
}
