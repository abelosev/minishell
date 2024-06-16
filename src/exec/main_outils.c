/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 03:14:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 19:07:57 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

t_list_env	*get_mini_env(void)
{
	t_list_env	*mini_env;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	mini_env = ft_new_env_node("PWD", cwd);
	if (ft_add_to_msh_env(&mini_env, "SHLVL=1"))
	{
		free(cwd);
		free_envp_list(mini_env);
		return (NULL);
	}
	if (ft_add_to_msh_env(&mini_env, "_=/usr/bin/env"))
	{
		free(cwd);
		free_envp_list(mini_env);
		return (NULL);
	}
	return (mini_env);
}

t_list_env	*change_shlvl(t_list_env *env)
{
	char		*prev;
	char		*new;
	int			new_sh;

	prev = get_value_by_key(env, "SHLVL");
	if (!prev)
		return (NULL);
	new_sh = ft_atoi(prev) + 1;
	free(prev);
	prev = ft_itoa(new_sh);
	if (!prev)
		return (NULL);
	new = ft_strjoin("SHLVL=", prev);
	if (!new)
		return (free(prev), NULL);
	if (ft_export_replace_or_add(&env, new))
		return (free(new), free(prev), NULL);
	return (free(new), free(prev), env);
}

char	*get_line(char *prompt)
{
	char	*line;

	rl_catch_signals = 0;
	rl_outstream = stderr;
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = readline (prompt);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	rl_outstream = stdout;
	if (errno == EINTR)
		g_status = 130;
	return (line);
}

int	check_line(char *line, int *code)
{
	if (!(*line) || only_spaces(line) || ft_strcmp(line, ":") == 0
		|| ft_strcmp(line, "!") == 0)
	{
		if (ft_strcmp(line, ":") == 0 || ft_strcmp(line, "!") == 0)
			add_history(line);
		if (ft_strcmp(line, "!") == 0)
			*code = 1;
		free(line);
		return (1);
	}
	return (0);
}

int	check_group(t_main *parsed, char *line, int *code)
{
	if (parsed->group->flag_fail == 2)
	{
		*code = 2;
		free(line);
		free_main(parsed);
		return (1);
	}
	return (0);
}
