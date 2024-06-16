/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   envp_get_tab.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 02:22:16 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 23:18:49 by abelosev		 ###   ########.fr	   */
/*																			*/
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

char	*create_env_entry(const char *key, const char *value)
{
	char	*tmp1;
	char	*res;

	if (value && !ft_strchr(key, '='))
	{
		tmp1 = ft_strjoin(key, "=");
		if (!tmp1)
			return (NULL);
		res = ft_strjoin(tmp1, value);
		free(tmp1);
	}
	else if (value)
		res = ft_strjoin(key, value);
	else
		res = ft_strdup(key);
	if (!res)
		return (NULL);
	return (res);
}

int	fill_env_array(char **envp, t_list_env *list)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		envp[i] = create_env_entry(list->key, list->value);
		if (!envp[i])
		{
			free_tab(envp);
			return (0);
		}
		list = list->next;
		i++;
	}
	envp[i] = NULL;
	return (1);
}

char	**get_envp(t_list_env *list)
{
	char	**envp;

	envp = malloc(sizeof(char *) * (get_node_nb(list) + 1));
	if (!envp)
		return (NULL);
	if (!fill_env_array(envp, list))
		return (NULL);
	return (envp);
}
