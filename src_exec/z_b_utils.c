/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_b_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:03:04 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 20:54:20 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/minishell.h"

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

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}



//+ exec in param to return int exec->status
//+ int in param for builtins

int	ft_builtins(t_exec *exec, t_group *group, t_list_env **env_lst, t_built *fd)
{
	if (exec->pid <= 0)
	{
		if (ft_strncmp(group->cmd[0], "cd", 2) == 0)
			exec->stat = builtin_cd(group, group->cmd[1], env_lst, fd);
		else if (ft_strncmp(group->cmd[0], "env", 3) == 0)
			exec->stat = builtin_env(group, env_lst);
		else if (ft_strncmp(group->cmd[0], "pwd", 3) == 0)
			exec->stat = builtin_pwd(group, fd);
		else if (ft_strncmp(group->cmd[0], "echo", 4) == 0)
			exec->stat = builtin_echo(group, fd);
		else if (ft_strncmp(group->cmd[0], "unset", 5) == 0)
			exec->stat = builtin_unset(group, env_lst);
		else if (ft_strncmp(group->cmd[0], "export", 6) == 0)
			exec->stat = builtin_export(group, env_lst);
	}
	else
		waitpid(exec->pid, NULL, 0);
	return (exec->stat);
}

// close + revert
//print sur STDERR IN et OUT actuels
