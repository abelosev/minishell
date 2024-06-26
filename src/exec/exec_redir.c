/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:17:58 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/25 16:18:42 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_group *group)
{
	return (group->redir_in || group->redir_out || group->app_out);
}

int	open_redir(t_group *group, int *fd_in, int *fd_out)
{
	if (group->redir_in)
	{
		*fd_in = open(group->redir_in, O_RDONLY);
		if (*fd_in < 0)
			return (1);
	}
	if (group->app_out)
	{
		*fd_out = open(group->app_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd_out < 0)
			return (1);
	}
	else if (group->redir_out)
	{
		*fd_out = open(group->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd_out < 0)
			return (1);
	}
	return (0);
}

int	do_redir(t_main *p, t_list_env *env, t_exec *e, int *code)
{
	int		new_fd_in;
	int		new_fd_out;
	t_group	*group;

	group = p->group;
	new_fd_in = e->fd_in;
	new_fd_out = e->fd_out;
	if (open_redir(group, &new_fd_in, &new_fd_out))
		return (1);
	if (is_built(group->cmd[0]) != 0)
		exec_builtin(p, env, e, code);
	else
		ft_cmd(group, env, e, code);
	if (new_fd_in != e->fd_in)
	{
		close(new_fd_in);
		dup2(STDIN_FILENO, e->fd_in);
	}
	if (new_fd_out != e->fd_out)
	{
		close(new_fd_out);
		dup2(STDOUT_FILENO, e->fd_out);
	}
	return (*code);
}
