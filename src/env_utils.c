/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:15:51 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 10:24:32 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env_node(char *s)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(s);
		return (NULL);
	}
	new->line = s;
	new->next = NULL;
	return (new);
}

void	ft_add_env(t_env *lst, t_env *new)
{
	if (!new)
		return ;
	if (lst == NULL)
	{
		lst = new;
		return ;
	}
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
}

t_env	*ft_find_in_env(t_env *env, char *target, int target_len)
{
	t_env	*p;
	int		env_len;
	int		len;

	p = env;
	while (p)
	{
		env_len = 0;
		while (p->line[env_len] != '\0' && p->line[env_len] != '=')
			env_len++;
		if (env_len > target_len)
			len = env_len;
		else
			len = target_len;
		if (ft_strncmp(&p->line[0], target, len) == 0)
			return (p);
		p = p->next;
	}
	return (NULL);
}

int	ft_add_to_msh_env(t_env *env, char *new_str)
{
	ft_add_env(env, ft_new_env_node(new_str));
	return (0);
}
