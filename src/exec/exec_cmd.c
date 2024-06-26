/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:12:28 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/26 18:02:57 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_child(t_group *group, char **new_envp, t_exec *e)
{
	if (e->fd_in != STDIN_FILENO)
	{
		dup2(e->fd_in, STDIN_FILENO);
		close(e->fd_in);
	}
	if (e->fd_out != STDOUT_FILENO)
	{
		dup2(e->fd_out, STDOUT_FILENO);
		close(e->fd_out);
	}
	execve(group->cmd[0], group->cmd, new_envp);
}

void	ft_cmd(t_group *group, t_list_env *env, t_exec *e, int *code)
{
	pid_t	pid;
	char	**new_envp;

	new_envp = get_envp(env);
	if (!new_envp)
	{
		*code = 1;
		return ;
	}
	pid = fork();
	if (pid == 0)
		ft_cmd_child(group, new_envp, e);
	else if (pid > 0)
	{
		if (e->fd_in != STDIN_FILENO)
			close(e->fd_in);
		if (e->fd_out != STDOUT_FILENO)
			close(e->fd_out);
	}
	else
		*code = 1;
	free_tab(new_envp);
	e->cpid[e->cpid_index] = pid;
	e->last_pid = pid;
}

void	execute_command(t_main *p, t_list_env *env, t_exec *e, int *code)
{
	if (is_built(p->group->cmd[0]) != 0)
		exec_builtin(p, env, e, code);
	else
	{
		ft_cmd(p->group, env, e, code);
	}
}
