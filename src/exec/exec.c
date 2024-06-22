/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:20:07 by aauthier          #+#    #+#             */
/*   Updated: 2024/06/16 19:49:33 by abelosev         ###   ########.fr       */
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
        exec_builtin(p->group, env, p, e->fd_out, code);
    else
        ft_cmd(p->group, env, e->fd_in, e->fd_out, code);
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
        exit(1);
    }
	else
	{
		// exec->last_pid = pid; 
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
    do_redir(p->group, p, env, e->fd_in, e->fd_out, code);
    close(e->fd_out);
    if (p->group->next)
        create_pipe_and_fork(p, env, e, code);
}

void ft_exec(t_main *p, t_list_env *env, int *code)
{
    t_group *start;
	t_exec	e;

	start = p->group;
	e.group_count = group_nb(p->group);
	// e.num_pipes = e.group_count - 1;
	e.fd_in = get_hd_fd(p, env, code);
	e.pipes = NULL;
	e.pipe_index = 0;
	e.last_pid = -1;

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
		else if (p->group->flag_fail != 0)
            *code = p->group->flag_fail;

        if (e.fd_in != STDIN_FILENO)
            close(e.fd_in);
        if (p->group->next)
		{
            close(e.pipes[e.pipe_index][1]);
            e.fd_in = e.pipes[e.pipe_index][0];
            e.pipe_index += 1;
        }
        p->group = p->group->next;
    }
    // ft_wait((group_count - 1), pipes, code);

	// if (exec.last_pid != -1)
    // {
    //     int status;
    //     waitpid(exec.last_pid, &status, 0);
    //     if (WIFEXITED(status))
    //         *(exec.code) = WEXITSTATUS(status);
    //     else
    //         *(exec.code) = 1;
    // }
    if(e.group_count > 1)
		close_all_pipes(e.pipes, e.group_count - 1);
	p->group = start;
    if (p)
        free_main(p);
}
