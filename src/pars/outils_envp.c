/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   outils_envp.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 02:23:15 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 02:40:40 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

t_list_env	*ft_new_env_node(char *key, char *value)
{
	t_list_env	*new;

	new = malloc(sizeof(t_list_env));
	if (!new)
	{
		free(key);
		free(value);
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_list_env	*ft_find_in_env(t_list_env *env, char *target_key)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, target_key, ft_strlen(target_key)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_add_env(t_list_env **lst, t_list_env *new_node)
{
	t_list_env	*current;

	if (!new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

int	ft_add_to_msh_env(t_list_env **env, char *new_str)
{
	t_list_env	*new_node;

	new_node = malloc(sizeof(t_list_env));
	if (!new_node)
		return (1);
	new_node->key = get_key(new_str);
	new_node->value = get_value(new_str);
	new_node->next = NULL;
	ft_add_env(env, new_node);
	return (0);
}

char	*get_value_by_key(t_list_env *env, char *target)
{
	char	*prev;

	prev = NULL;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, target) == 0)
		{
			prev = ft_strdup(env->value);
			if (!prev)
				return (NULL);
		}
		env = env->next;
	}
	return (prev);
}
