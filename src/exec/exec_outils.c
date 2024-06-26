/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:01:53 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/26 18:02:35 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *name, int type, int code)
{
	if (type == 0)
	{
		if (name == NULL)
			perror("minishell");
		else
		{
			ft_putstr_err("minishell: ");
			perror(name);
		}
	}
	if (type == 1 && name)
	{
		ft_putstr_err("minishell: ");
		ft_putstr_err(name);
		ft_putstr_err(": command not found\n");
	}
	return (code);
}

int	get_hd_fd(t_main *p, t_list_env *env, int *code)
{
	int		fd_hd;
	char	*file_hd;

	if (p->hd_del == NULL)
		return (STDIN_FILENO);
	file_hd = heredoc(env, p->hd_del, code);
	if (!file_hd)
		return (STDIN_FILENO);
	fd_hd = open(file_hd, O_RDONLY);
	free(file_hd);
	if (fd_hd < 0)
		return (STDIN_FILENO);
	return (fd_hd);
}

void	init_cpid(t_main *p, t_exec *e)
{
	int		i;
	t_group	*start;

	i = 0;
	start = p->group;
	while (i < e->group_count)
	{
		if (p->group->flag_fail != 0 || ((!p->group->cmd[0]
					|| (is_built(p->group->cmd[0])))))
			e->cpid[i] = -1;
		else
			e->cpid[i] = 0;
		i++;
		p->group = p->group->next;
	}
	p->group = start;
}

int	init_exec(t_main *p, t_list_env *env, t_exec *e, int *code)
{
	e->group_count = group_nb(p->group);
	e->fd_in = get_hd_fd(p, env, code);
	if (g_status)
		return (1);
	e->fd_out = STDOUT_FILENO;
	e->pipes = NULL;
	e->pipe_index = 0;
	e->cpid = malloc(sizeof(pid_t) * e->group_count);
	if (!e->cpid)
		return (1);
	e->pipe_fd[0] = -1;
	e->pipe_fd[1] = -1;
	e->last_pid = -1;
	e->cpid_index = 0;
	e->last_flag = -1;
	init_cpid(p, e);
	return (0);
}

int	ft_wait(t_exec *e, int *code)
{
	int	i;

	i = 0;
	while (i < e->group_count)
	{
		if (e->cpid[i] != -1)
		{
			waitpid(e->cpid[i], code, 0);
		}
		i++;
	}
	if (WIFEXITED(*code))
		return (WEXITSTATUS(*code));
	return ((WTERMSIG(*code) + 128));
}
