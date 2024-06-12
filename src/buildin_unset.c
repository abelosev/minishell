/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:16:20 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/04 10:44:15 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_vector_size(char **vector)
{
	int	i;

	i = 0;
	while (vector[i] != NULL)
		i++;
	return (i);
}

int	ft_remove_from_env(t_env *env, t_env *the_rm_env)
{
	t_env	*pos;

	if (!env || !the_rm_env)
		return (ft_error(NULL, 0, 1));
	if (env == the_rm_env)
	{
		env = the_rm_env->next;
		free(the_rm_env->line);
		free(the_rm_env);
		return (0);
	}
	pos = env;
	while (pos != NULL && pos->next != the_rm_env)
		pos = pos->next;
	if (pos != NULL)
	{
		pos->next = the_rm_env->next;
		free(the_rm_env->line);
		free(the_rm_env);
		return (0);
	}
	return (ft_error(NULL, 0, 1));
}

int	ft_unset_is_valid(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		write(2, "minishell: unset: `", 20);
		write(2, str, ft_strlen(str));
		write(2, "\': not a valid identifier\n", 26);
		return (0);
	}
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			write(2, "minishell: unset: `", 20);
			write(2, str, ft_strlen(str));
			write(2, "\': not a valid identifier\n", 26);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(char **args, t_env *env)
{
	int		i;
	int		error_flag;
	t_env	*the_env;

	i = 1;
	error_flag = 0;
	while (args[i] != NULL)
	{
		if (ft_unset_is_valid(args[i]))
		{
			if (ft_str_contains_char(args[i], '='))
				the_env = NULL;
			else
				the_env = ft_find_in_env(env, args[i], ft_strlen(args[i]));
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
