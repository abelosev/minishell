/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_get_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:12:10 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/16 14:02:21 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include "../../inc/minishell.h"

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
		if(list->value)
		{
			if(!ft_strchr(list->key, '='))
			{
				tmp1 = ft_strjoin(list->key, "=");
				envp[i] = ft_strjoin(tmp1, list->value);
				free(tmp1);
			}
			else
				envp[i] = ft_strjoin(list->key, list->value);
		}
		else
			envp[i] = ft_strdup(list->key);				//добавлено для того, чтобы правильно сделать export
		list = list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
