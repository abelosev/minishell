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

void	close_all_pipes(int **pipes, int num_pipes)
{
	int i;

	i = 0;
	while(i < num_pipes)
	{
        close(pipes[i][0]);
        close(pipes[i][1]);
		i++;
    }
	free_tab_int(pipes, num_pipes);
}

void execute_command(t_main *p, t_list_env *env, t_exec *e, int *code)
{
    if (is_built(p->group->cmd[0]) != 0)
        exec_builtin(p, env, e, code);
    else
    {
        ft_cmd(p->group, env, e, code);
    }
}

void	create_pipe_and_fork(t_main *p, t_list_env *env, t_exec *e, int *code)
{
	pid_t pid;

    if (pipe(e->pipe_fd) == -1)
	{
        perror("pipe failed");
        *code = 1;
        return;
    }
    pid = fork();
    if (pid == -1)
	{
        perror("fork failed");
        *code = 1;
        return;
    }
	else if (pid == 0)
	{
        close(e->pipe_fd[0]);
        dup2(e->pipe_fd[1], STDOUT_FILENO);
        close(e->pipe_fd[1]);
		e->fd_out = STDOUT_FILENO;
        execute_command(p, env, e, code);
        *code = 1;
        return ;
    }
	else
	{
        close(e->pipe_fd[1]);
        e->fd_in = e->pipe_fd[0];
    }
}

void handle_redirection_and_fork(t_main *p, t_list_env *env, t_exec *e, int *code)
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
        create_pipe_and_fork(p, env, e, code);
}


void    init_exec(t_main *p, t_list_env *env, t_exec *e, int *code)
{
    int i;
    t_group *start;

    i = 0;
    start = p->group;
    e->group_count = group_nb(p->group);
	e->fd_in = get_hd_fd(p, env, code);
    e->fd_out = STDOUT_FILENO;
	e->pipes = NULL;
	e->pipe_index = 0;
    e->cpid = malloc(sizeof(pid_t) * e->group_count); //add protection
    e->pipe_fd[0] = -1;
    e->pipe_fd[1] = -1;   
	e->last_pid = -1;
    e->cpid_index = 0;
    while(i < e->group_count)
    {
        if(p->group->flag_fail != 0 || ((!p->group->cmd[0] || (is_built(p->group->cmd[0])))))
            e->cpid[i] = -1;
        else
            e->cpid[i] = 0;
        i++;
        p->group = p->group->next; 
    }
    p->group = start;
}

void    ft_exec(t_main *p, t_list_env *env, int *code)
{
    t_group *start;
	t_exec  e;
	int		last_flag;

	last_flag = 0;
	start = p->group;
    init_exec(p, env, &e, code);
    if (e.group_count > 1)
	{
		if(create_pipes((e.group_count - 1), &e.pipes) != 0)
		{
			*code = 1;
			return ;
		}
	}
    while (p->group)
	{
        e.fd_out = STDOUT_FILENO;
        if (p->group->next)
            e.fd_out = e.pipes[e.pipe_index][1];
        if (p->group->flag_fail == 0 && p->group->cmd && *(p->group->cmd))
		{
            if (is_redir(p->group))
                handle_redirection_and_fork(p, env, &e, code);
			else
                execute_command(p, env, &e, code);
        }
		if(p->group->flag_fail != 0)					// what about builtins?
		{
			*code = p->group->flag_fail;
			if(!p->group->next)
				last_flag = p->group->flag_fail;
		}
        if (e.fd_in != STDIN_FILENO)
            close(e.fd_in);
        if (p->group->next)
		{
            close(e.pipes[e.pipe_index][1]);
            e.fd_in = e.pipes[e.pipe_index][0];
            e.pipe_index += 1;
        }
        p->group = p->group->next;
        e.cpid_index++;
    }
    ft_wait(&e, code);
    if(e.group_count > 1)
		close_all_pipes(e.pipes, e.group_count - 1);
	p->group = start;
    if (p)
        free_main(p);
    if(e.cpid)
        free(e.cpid);
	if(last_flag != 0)
		*code = last_flag;
}
