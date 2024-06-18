/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_get_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 02:22:16 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 03:08:38 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	get_node_nb(t_list_env *list)
{
	int	node_nb;

	node_nb = 0;
	while (list != NULL)
	{
		list = list->next;
		node_nb++;
	}
	return (node_nb);
}

char	**get_envp(t_list_env *list)
{
	char	**envp;
	char	*tmp1;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (get_node_nb(list) + 1));
	if (!envp)
		return (NULL);
	while (list != NULL)
	{
		if (list->value)
		{
			if (!ft_strchr(list->key, '='))
			{
				tmp1 = ft_strjoin(list->key, "=");
				if (!tmp1)
					return (free_tab(envp), NULL);
				envp[i] = ft_strjoin(tmp1, list->value);
				free(tmp1);
				if (!envp[i])
					return (free_tab(envp), NULL);
			}
			else
			{
				envp[i] = ft_strjoin(list->key, list->value);
				if (!envp[i])
					return (free_tab(envp), NULL);
			}
		}
		else
		{
			envp[i] = ft_strdup(list->key);
			if (!envp[i])
					return (free_tab(envp), NULL);
		}
		list = list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
