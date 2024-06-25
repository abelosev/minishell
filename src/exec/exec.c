/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:20:07 by aauthier          #+#    #+#             */
/*   Updated: 2024/06/24 20:02:19 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe_and_fork(t_main *p, t_list_env *env, t_exec *e, int *code) // code???
{
	pid_t pid;

    if (pipe(e->pipe_fd) == -1)
        return (perror("pipe failed"), 1);
    pid = fork();
    if (pid == -1)
        return (perror("fork failed"), 1);
	if (pid == 0)
	{
        close(e->pipe_fd[0]);
        dup2(e->pipe_fd[1], STDOUT_FILENO);
        close(e->pipe_fd[1]);
		e->fd_out = STDOUT_FILENO;
        execute_command(p, env, e, code);
        return (1);
    }
	close(e->pipe_fd[1]);
    e->fd_in = e->pipe_fd[0];
    return (0);
}

void	handle_redirection_and_fork(t_main *p, t_list_env *env, t_exec *e, int *code)
{
    if (open_redir(p->group, &e->fd_in, &e->fd_out) || e->fd_out < 0)
	{
        ft_putstr_err("open output failed\n");
        *code = 1;
        return;
    }
    do_redir(p, env, e, code);
    close(e->fd_out);
    if (p->group->next)
        *code = create_pipe_and_fork(p, env, e, code);
}

void	process_group(t_main *p, t_list_env *env, t_exec *e, int *code)
{
    e->fd_out = STDOUT_FILENO;
    if (p->group->next)
        e->fd_out = e->pipes[e->pipe_index][1];
    if (p->group->flag_fail == 0 && p->group->cmd && *(p->group->cmd))
    {
        if (is_redir(p->group))
            handle_redirection_and_fork(p, env, e, code);
        else
            execute_command(p, env, e, code);
    }
    if (p->group->flag_fail != 0)  // Handle flag_fail
    {
        *code = p->group->flag_fail;
        if (!p->group->next)
            e->last_flag = p->group->flag_fail;
    }
    if (e->fd_in != STDIN_FILENO)
        close(e->fd_in);
    if (p->group->next)
    {
        close(e->pipes[e->pipe_index][1]);
        e->fd_in = e->pipes[e->pipe_index][0];
        e->pipe_index += 1;
    }
}

void	ft_exec_loop(t_main *p, t_list_env *env, t_exec *e, int *code)
{
	while (p->group)
	{
		process_group(p, env, e, code);
        p->group = p->group->next;
        e->cpid_index++;
    }
}

int    ft_exec(t_main *p, t_list_env *env, int *code)
{
    t_group *start;
	t_exec  e;

	start = p->group;
    init_exec(p, env, &e, code);
    if (e.group_count > 1)
	{
		if(create_pipes((e.group_count - 1), &e.pipes) != 0)
			return (1);
	}
	signal(SIGQUIT, &sigquit_handler);	//???
	ft_exec_loop(p, env, &e, code);
    *code = ft_wait(&e, code);
    if(e.group_count > 1)
		close_all_pipes(e.pipes, e.group_count - 1);
	p->group = start;
    if (p)
        free_main(p);
    if(e.cpid)
        free(e.cpid);
	if(e.last_flag != 0)
		*code = e.last_flag;
	return (*code);
}
