/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:20:07 by aauthier          #+#    #+#             */
/*   Updated: 2024/06/16 19:49:33 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir(t_group *group)
{
    return (group->redir_in || group->redir_out || group->app_out);
}

int open_redir(t_group *group, int *fd_in, int *fd_out)
{
    if (group->redir_in)
    {
        *fd_in = open(group->redir_in, O_RDONLY);
        if (*fd_in < 0)
            return 1;
    }
    if (group->app_out)
    {
        *fd_out = open(group->app_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (*fd_out < 0)
            return 1;
    }
    else if (group->redir_out)
    {
        *fd_out = open(group->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (*fd_out < 0)
            return 1;
    }
    return 0;
}

void exec_builtin(t_group *group, t_list_env *env, t_main *p, int fd_out, int *code)
{
    *code = ft_do_builtin(group, env, fd_out, code);
    if (is_built(group->cmd[0]) == B_EXIT)
    {
        ft_putstr_err("exit\n");
        free_envp_list(env);
        if (p)
            free_main(p);
        clear_history();
        exit(*code);
    }
}

void ft_cmd(t_group *group, t_list_env *env, int fd_in, int fd_out, int *code)
{
    pid_t pid;
    char **new_envp;
	
	new_envp = get_envp(env);
    if (!new_envp)
    {
        *code = 1;
        return;
    }
    pid = fork();
    if (pid == 0)
    {
        if (fd_in != STDIN_FILENO)
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (fd_out != STDOUT_FILENO)
        {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        execve(group->cmd[0], group->cmd, new_envp);
        *code = 1;
		return ;
    }
    else if (pid > 0)
    {
        if (fd_in != STDIN_FILENO)
            close(fd_in);
        if (fd_out != STDOUT_FILENO)
            close(fd_out);
    }
    else
        *code = 1;
    free_tab(new_envp);
}


// void wait_for_children(int *code)
// {
//     int status;
//     pid_t pid;

//     while ((pid = wait(&status)) > 0)
//     {
//         if (WIFEXITED(status))
//             *code = WEXITSTATUS(status);
//         else if (WIFSIGNALED(status))
//         {
//             *code = WTERMSIG(status) + 128;
//             if (WTERMSIG(status) == SIGINT)
//                 write(STDERR_FILENO, "\n", 1);
//             else if (WTERMSIG(status) == SIGQUIT)
//                 write(STDERR_FILENO, "Quit (core dumped)\n", 19);
//         }
//         else
//             *code = 1;
//     }
// }

void	do_redir(t_group *group, t_main *p, t_list_env *env, int fd_in, int fd_out, int *code) //to fix the 5 parameters situation
{
    int new_fd_in;
    int new_fd_out;

	new_fd_in = fd_in;
	new_fd_out = fd_out;
    if (open_redir(group, &new_fd_in, &new_fd_out))
    {
        *code = 1;
        return ;
    }
    if (is_built(group->cmd[0]) != 0)
		exec_builtin(group, env, p, fd_out, code);
	else
		ft_cmd(group, env, fd_in, fd_out, code);
    if (new_fd_in != fd_in)
	{
		close(new_fd_in);
		dup2(STDIN_FILENO, fd_in);
	}
    if (new_fd_out != fd_out)
	{
		close(new_fd_out);
		dup2(STDOUT_FILENO, fd_out);
	}
    // if(p)
    //     free_main(p);
    // return (status);
}

void	ft_exec(t_main *p, t_list_env *env, int *code)
{
    t_group *curr;
    int fd_in;
	int file_fd;
	int fd_out;
    int pipefd[2];
	char buffer[4096];		//можно ли так делать?
    ssize_t bytes_read;
    // int e_status;
    int pipe_res;

	fd_in = get_hd_fd(p, env, code);	// передавать ли fd_in параметром (?)
    curr = p->group;
    pipe_res = 0;
    while (curr)
    {
        if (curr->next)
        {
			pipe_res = pipe(pipefd);
            if (pipe_res == -1)
            {
                if(p)
                    free_main(p);
                ft_putstr_err("pipe failed");
                *code = 1;
                return ; // не удалось открыть пайп   
            }
        }

        if (curr->flag_fail == 0 && curr->cmd && *(curr->cmd))
        {
            if (is_redir(curr))
            {
                if(open_redir(curr, &fd_in, &fd_out) || fd_out < 0)
                {
                    if(p)
                        free_main(p);
                    ft_putstr_err("open output failed");
                    *code = 1;
                    return ;
                }
                    
                do_redir(curr, p, env, fd_in, fd_out, code);
                close(fd_out);
                if (curr->next)
                {
                    file_fd = open(curr->redir_out, O_RDONLY);
                    if (file_fd < 0)
                    {
                        if(p)
                            free_main(p);
                        ft_putstr_err("open output file failed");
                        *code = 1;
                        return ;
                    }
                    while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0)
                        write(pipefd[1], buffer, bytes_read);
                    close(file_fd);
                    close(pipefd[1]);
                    fd_in = pipefd[0];
                }
            }
            else
            {
                if (is_built(curr->cmd[0]) != 0)
				{
					if (curr->next)
						exec_builtin(curr, env, p, pipefd[1], code);
					else
						exec_builtin(curr, env, p, STDOUT_FILENO, code);
				}
                else
                {
					if (curr->next)
    					ft_cmd(curr, env, fd_in, pipefd[1], code);
					else
    					ft_cmd(curr, env, fd_in, STDOUT_FILENO, code);
				}
			}
        }
        else
            *code = curr->flag_fail;

        if (fd_in != STDIN_FILENO)
            close(fd_in);
        if (pipe_res != 0 && pipefd[1] != STDOUT_FILENO)
            close(pipefd[1]);
		if (curr->next)
            fd_in = pipefd[0];
        curr = curr->next;
    }
    if (fd_in != STDIN_FILENO)
        close(fd_in);
    if(p)
        free_main(p);
    // return (status);
}

