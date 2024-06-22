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

void execute_command(t_main *p, t_list_env *env, int *code, t_group *curr, int fd_in, int fd_out)
{
    if (is_built(curr->cmd[0]) != 0)
        exec_builtin(curr, env, p, fd_out, code);
    else
        ft_cmd(curr, env, fd_in, fd_out, code);
}

void	create_pipe_and_fork(t_main *p, t_list_env *env, int *code, t_group *curr, int *fd_in, int pipe_fd[2])
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
        execute_command(p, env, code, curr, *fd_in, STDOUT_FILENO);
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

void handle_redirection_and_fork(t_main *p, t_list_env *env, int *code, t_group *curr, int *fd_in, int *fd_out, int pipe_fd[2])
{
    if (open_redir(curr, fd_in, fd_out) || *fd_out < 0)
	{
        ft_putstr_err("open output failed\n");
        *code = 1;
        return;
    }
    do_redir(curr, p, env, *fd_in, *fd_out, code);
    close(*fd_out);
    if (curr->next)
        create_pipe_and_fork(p, env, code, curr, fd_in, pipe_fd);
}

void ft_exec(t_main *p, t_list_env *env, int *code)
{
    t_group *curr = p->group;
    int group_count = group_nb(curr);
    int fd_in = get_hd_fd(p, env, code);
    int fd_out;
    int **pipes = NULL;
    int num_pipes = group_count - 1;
    int pipe_index = 0;
    int pipe_fd[2];
	// exec.last_pid = -1;

    if (group_count > 1)
	{
		if(create_pipes((num_pipes) * 2, &pipes) != 0)
		{
			*code = 1;
			return ;
		}
	}
    while (curr)
	{
        fd_out = STDOUT_FILENO;
        if (curr->next)
            fd_out = pipes[pipe_index][1];
        if (curr->flag_fail == 0 && curr->cmd && *(curr->cmd))
		{
            if (is_redir(curr))
                handle_redirection_and_fork(p, env, code, curr, &fd_in, &fd_out, pipe_fd);
			else
                execute_command(p, env, code, curr, fd_in, fd_out);
        }
		else if (curr->flag_fail != 0)
            *code = curr->flag_fail;

        if (fd_in != STDIN_FILENO)
            close(fd_in);
        if (curr->next)
		{
            close(pipes[pipe_index][1]);
            fd_in = pipes[pipe_index][0];
            pipe_index += 1;
        }
        curr = curr->next;
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
    if(group_count > 1)
		close_all_pipes(pipes, num_pipes);
    if (p)
        free_main(p);
}
