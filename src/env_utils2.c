/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:24:43 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 12:38:47 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->line != NULL)
		{
			lst_len += ft_strlen(lst->line);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(sizeof(char) * size_env(lst) + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->line != NULL)
		{
			j = 0;
			while (lst->line[j])
				env[i++] = lst->line[j++];
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

char	*ft_get_env(t_env *env, char *var_name)
{
	t_env	*the_env;
	int		len;

	len = ft_strlen(var_name);
	if (len == 0)
		return (NULL);
	the_env = ft_find_in_env(env, var_name, len);
	if (!the_env)
		return (NULL);
	return (the_env->line + len + 1);
}

char	**create_env_arr(t_env *env)
{
	char	*p;
	char	**env_arr;

	p = env_to_str(env);
	env_arr = ft_split(p, '\n');
	free(p);
	return (env_arr);
}
