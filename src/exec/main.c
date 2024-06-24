/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 03:14:34 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/24 15:02:26 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	exit_minishell(t_list_env *env, char *line, t_main *p, int code)
{
	// ft_putstr_err("exit\n");
	free_envp_list(env);
	if (line)
		free(line);
	clear_history();
	if (p)
		free_main(p);
	exit(code);
}

void	minishell_loop(t_list_env *env, int *code)
{
	char		*line;
	t_main		*parsed;

	while (1)
	{
		line = get_line(">$ ");
		if (!line)
			exit_minishell(env, line, NULL, 1);
		if (check_line(line, code))
			continue ;
		add_history(line);
		parsed = parser(line, env, code);
		if (!parsed)
			exit_minishell(env, line, parsed, 1);
		// print_group_list(parsed->group);
		if (check_group(parsed, line, code))
			continue ;
		if (line)
			free(line);
		ft_exec(parsed, env, code);//changer pour void plus tard
	}
	if (parsed)
		free_main(parsed);
	if(env)
		free_envp_list(env);
	clear_history();
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	minishell_loop(new_env, &code);
	if(new_env)
		free_envp_list(new_env);
	if (g_status != 0) //to make sure
		code = g_status;
	return (code);
}
