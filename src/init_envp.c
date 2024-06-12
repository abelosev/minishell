/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:33:25 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/04 10:37:59 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_enp_ext(t_env **env, t_env **mini_env, t_env *new)
{
	if (!*env)
	{
		*env = new;
		*mini_env = *env;
	}
	else
	{
		(*env)->next = new;
		*env = new;
	}
}

int	init_envp(t_mini *mini, char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	i = 0;
	env = NULL;
	new = NULL;
	while (envp && envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->line = ft_strdup(envp[i]);
		new->next = NULL;
		init_enp_ext(&env, &mini->env, new);
		i++;
	}
	return (0);
}

void	ft_free_envp(t_env *env)
{
	t_env	*next;

	if (!env)
		return ;
	while (env)
	{
		free(env->line);
		next = env->next;
		free(env);
		env = next;
	}
}
