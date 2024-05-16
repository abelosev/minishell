/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_b_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:03:04 by memarign          #+#    #+#             */
/*   Updated: 2024/05/11 03:05:35 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//get path from varname
char	*set_path(t_list_env *env_lst, char *key)
{
	char	*path;

	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
		{
			path = env_lst->value;
			return (path);
		}
		else
			env_lst = env_lst->next;
	}
	return (NULL);
}

//changed
int	is_built2(char *str)
{
	int		i;
	char	*tab[7];

	i = 0;
	tab[0] = "cd";
	tab[1] = "env";
	tab[2] = "pwd";
	tab[3] = "echo";
	tab[4] = "exit";
	tab[5] = "unset";
	tab[6] = "export";
	while (i <= 6)
	{
		if (ft_strncmp(str, tab[i], ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

//+ exec in param to return int exec->status
//+ int in param for builtins

int	ft_builtins(t_exec *exec, t_group *group, t_list_env *env_lst)
{
	if (ft_strncmp(group->cmd[0], "cd", 2) == 0)
		exec->status = builtin_cd(group, group->cmd[1], env_lst);
	else if (ft_strncmp(group->cmd[0], "env", 3) == 0)
		exec->status = builtin_env(group, env_lst);
	else if (ft_strncmp(group->cmd[0], "pwd", 3) == 0)
		exec->status = builtin_pwd(group);
	else if (ft_strncmp(group->cmd[0], "echo", 4) == 0)
		exec->status = builtin_echo(group);
	else if (ft_strncmp(group->cmd[0], "unset", 5) == 0)
		exec->status = builtin_unset(group, env_lst);
	else if (ft_strncmp(group->cmd[0], "export", 6) == 0)
		exec->status = builtin_export(group, env_lst);
	return (exec->status);
}
