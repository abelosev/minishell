/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:06:45 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/26 18:08:23 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

t_list_env	*get_mini_env(void)
{
	t_list_env	*mini_env;
	t_list_env	*new_node;
	char		*cwd;

	mini_env = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	new_node = ft_new_env_node(strdup("PWD"), cwd);
	if (!new_node)
		return (free(cwd), NULL);
	ft_add_env(&mini_env, new_node);
	new_node = ft_new_env_node(strdup("SHLVL"), strdup("1"));
	if (!new_node)
		return (free_envp_list(mini_env), NULL);
	ft_add_env(&mini_env, new_node);
	new_node = ft_new_env_node(strdup("_"), strdup("/usr/bin/env"));
	if (!new_node)
		return (free_envp_list(mini_env), NULL);
	ft_add_env(&mini_env, new_node);
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
