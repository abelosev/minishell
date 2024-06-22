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

void execute_command(t_main *p, t_list_env *env, int *code, int fd_in, int fd_out)
{
    if (is_built(p->group->cmd[0]) != 0)
        exec_builtin(p->group, env, p, fd_out, code);
    else
        ft_cmd(p->group, env, fd_in, fd_out, code);
}

void	create_pipe_and_fork(t_main *p, t_list_env *env, int *code, int *fd_in, int pipe_fd[2])
{
	pid_t pid;

    if (pipe(pipe_fd) == -1)
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
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        execute_command(p, env, code, *fd_in, STDOUT_FILENO);
        *code = 1;
        exit(1);
    }
	else
	{
		// exec->last_pid = pid; 
        close(pipe_fd[1]);
        *fd_in = pipe_fd[0];
    }
}

void handle_redirection_and_fork(t_main *p, t_list_env *env, int *code, int *fd_in, int *fd_out, int pipe_fd[2])
{
    if (open_redir(p->group, fd_in, fd_out) || *fd_out < 0)
	{
        ft_putstr_err("open output failed\n");
        *code = 1;
        return;
    }
    do_redir(p->group, p, env, *fd_in, *fd_out, code);
    close(*fd_out);
    if (p->group->next)
        create_pipe_and_fork(p, env, code, fd_in, pipe_fd);
}

typedef struct s_exec
{
	int group_count;
    int fd_in;
    int fd_out;
	int **pipes;
	int pipe_index;
	int pipe_fd[2];
	int last_pid;
}	t_exec;

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
                handle_redirection_and_fork(p, env, code, &e.fd_in, &e.fd_out, e.pipe_fd);
			else
                execute_command(p, env, code, e.fd_in, e.fd_out);
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
    // ft_wait((group_count - 1) * 2, pipes, code);
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
    if (p)
        free_main(p);
}
