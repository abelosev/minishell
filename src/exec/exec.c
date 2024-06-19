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

void	close_all_pipes(int pipes[][2], int num_pipes)
{
	int i;

	i = 0;
	while(i < num_pipes)
	{
        close(pipes[i][0]);
        close(pipes[i][1]);
		i++;
    }
}

void ft_exec(t_main *p, t_list_env *env, int *code)
{
    t_group *curr = p->group;
    int group_count = group_nb(curr);
    int fd_in = get_hd_fd(p, env, code);
	int fd_out;
    int pipes[(group_count - 1) * 2][2];
	int num_pipes = group_count - 1;
	int pipe_index = 0;
	int pipe_fd[2];

    if (group_count > 1)
        create_pipes((group_count - 1) * 2, pipes);
    while (curr)
	{
        fd_out = STDOUT_FILENO;
        if (curr->next)
		{
            fd_out = pipes[pipe_index][1];
        }
        if (curr->flag_fail == 0 && curr->cmd && *(curr->cmd))
		{
            if (is_redir(curr))
			{
                if (open_redir(curr, &fd_in, &fd_out) || fd_out < 0) {
                    ft_putstr_err("open output failed\n");
                    *code = 1;
                    return;
                }
                do_redir(curr, p, env, fd_in, fd_out, code);
                close(fd_out);
                if (curr->next)
				{
                    if (pipe(pipe_fd) == -1)
					{
                        perror("pipe failed");
                        *code = 1;
                        return;
                    }
                    pid_t pid = fork();
                    if (pid == -1)
					{
                        perror("fork failed");
                        *code = 1;
                        return;
                    } else if (pid == 0)
					{
                        close(pipe_fd[0]);
                        dup2(pipe_fd[1], STDOUT_FILENO);
                        close(pipe_fd[1]);
                        if (is_built(curr->cmd[0]) != 0)
                            exec_builtin(curr, env, p, STDOUT_FILENO, code);
                        else
                            ft_cmd(curr, env, fd_in, STDOUT_FILENO, code);
                        *code = 1;
                        exit(1);
                    } else
					{
                        close(pipe_fd[1]);
                        fd_in = pipe_fd[0];
                    }
                }
            } else
			{
                if (is_built(curr->cmd[0]) != 0)
                    exec_builtin(curr, env, p, fd_out, code);
                else
                    ft_cmd(curr, env, fd_in, fd_out, code);
            }
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
    ft_wait((group_count - 1) * 2, pipes, code);	/// à corriger !!
	close_all_pipes(pipes, num_pipes);
    if (p)
        free_main(p);
}