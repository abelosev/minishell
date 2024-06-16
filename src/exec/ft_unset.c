/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:12:44 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 19:13:55 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list_one_node(t_list_env *env)
{
	if (env)
	{
		free(env->key);
		free(env->value);
		free(env);
	}
}

int	ft_remove_from_env(t_list_env **env, t_list_env *the_rm_env)
{
	t_list_env	*pos;
	t_list_env	*prev;

	prev = NULL;
	if (!env || !the_rm_env)
		return (ft_error(NULL, 0, 1));
	if (*env == the_rm_env)
	{
		*env = the_rm_env->next;
		return (ft_free_list_one_node(the_rm_env), 0);
	}
	pos = *env;
	while (pos != NULL && pos != the_rm_env)
	{
		prev = pos;
		pos = pos->next;
	}
	if (pos == the_rm_env)
	{
		prev->next = the_rm_env->next;
		ft_free_list_one_node(the_rm_env);
		return (0);
	}
	return (ft_error(NULL, 0, 1));
}

int	ft_unset_is_valid(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_err("minishell: unset: `");
		ft_putstr_err(str);
		ft_putstr_err("\': not a valid identifier\n");
		return (0);
	}
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_err("minishell: unset: `");
			ft_putstr_err(str);
			write(2, "\': not a valid identifier\n", 26);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_group *group, t_list_env **env)
{
	int			i;
	int			error_flag;
	t_list_env	*the_env;

	i = 1;
	error_flag = 0;
	while (group->cmd[i] != NULL)
	{
		if (ft_unset_is_valid(group->cmd[i]))
		{
			the_env = ft_find_in_env(*env, group->cmd[i]);
			if (the_env != NULL)
			{
				if (ft_remove_from_env(env, the_env))
					return (1);
			}
		}
		else
			error_flag = 1;
		i++;
	}
	return (error_flag);
}
