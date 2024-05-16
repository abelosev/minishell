/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_get_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:46:31 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/16 14:02:19 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	separate_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_key(char *str)
{
	int		len;
	int		k;
	char	*key;

	len = separate_pos(str);
	k = 0;
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	while (k < len && str[k])
	{
		key[k] = str[k];
		k++;
	}
	key[k] = '\0';
	return (key);
}

char	*get_value(char *str)
{
	char	*value;
	int		i;
	int		k;
	int		len;

	i = separate_pos(str) + 1;
	k = 0;
	len = ft_strlen(str) - i;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	while (k < len)
	{
		value[k] = str[i];
		k++;
		i++;
	}
	value[k] = '\0';
	return (value);
}

t_list_env	*first_node(char **tab)
{
	t_list_env	*node;

	node = malloc(sizeof(t_list_env));
	if (!node)
		return (NULL);
	node->key = get_key(tab[0]);
	node->value = get_value(tab[0]);
	node->next = NULL;
	return (node);
}

t_list_env	*get_list(char **tab)
{
	int			i;
	t_list_env	*begin;
	t_list_env	*curr;

	begin = first_node(tab);
	curr = begin;
	i = 1;
	while (tab[i])
	{
		curr->next = malloc(sizeof(t_list_env));
		if (!curr->next)
		{
			free_envp_list(begin);
			return (NULL);
		}
		curr = curr->next;
		curr->key = get_key(tab[i]);
		curr->value = get_value(tab[i]);
		i++;
	}
	curr->next = NULL;
	return (begin);
}
