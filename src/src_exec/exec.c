/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 04:31:37 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 21:04:12 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

// add printf
// add checks
// think about exit
int ft_bin(t_exec *exec, t_group *group, t_list_env *env_lst)
{
    char **envp;
    pid_t pid;

    envp = get_envp(env_lst);

    pid = fork();
    if (pid == -1)
    {
        perror("Error exec fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        // Child process
        ft_redir(exec, group);
        exec->stat = execve(group->cmd[0], group->cmd, envp);
        perror("execve failed");
        exit(EXIT_FAILURE); // Exit if execve fails
    }
    else
    {
        // Parent process
        waitpid(pid, &exec->stat, 0);
        if (WIFEXITED(exec->stat))
            exec->stat = WEXITSTATUS(exec->stat);
        else if (WIFSIGNALED(exec->stat))
            exec->stat = 128 + WTERMSIG(exec->stat);
    }
    free_tab(envp);
    return (exec->stat);
}


int	simple_cmd(t_exec *exec, t_group *group, t_list_env **env_lst)
{
	t_built	fd;
	char **tab;

	if (group->app_in != NULL)
	{
		tab = get_here_doc(exec, group);
		if (!group->cmd)
		{
			free_tab(tab);
			return (0);
		}
		else
		{
			here_doc(exec, group);
			free_tab(tab);
			return (0);
		}
	}
	if (!group->cmd)
	{
		ft_redir2(exec, group);
		return (0);
	}
	if (is_built(group->cmd[0]))
	{
		ft_redir_b(exec, group, &fd);
		exec->stat = ft_builtins(exec, group, env_lst, &fd);
	}
	else
		ft_bin(exec, group, *env_lst);
	return (exec->stat);
}
