/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:20:07 by aauthier          #+#    #+#             */
/*   Updated: 2024/06/18 01:23:06 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static void close_pipefd(t_main *p, bool is_in_loop)
{
	if (p->pipefd[WRITE_END] > 0)
		close(p->pipefd[WRITE_END]);
	if (p->pipefd[TEMP_READ_END] > 0)
		close(p->pipefd[TEMP_READ_END]);
	if (!is_in_loop)
		if (p->pipefd[READ_END] > 0)
			close(p->pipefd[READ_END]);
}

int	is_redir(t_group *group)
{
	return(group->redir_in || group->redir_out || group->app_out);
}

int	open_redir(t_group *group, int *fd_in, int *fd_out)
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
	return (0);
}

int	exec_builtin(t_group *group, t_list_env *env, t_main *p, int *code)
{
	*code = ft_do_builtin(group, env, p->redir_fd[E_OUT], code);
	if(is_built(group->cmd[0]) == B_EXIT)
	{
		ft_putstr_err("exit\n");
		free_envp_list(env);
		if(p)
			free_parsed(p);
		clear_history();
		exit(*code);
	}
    return (*code);
}

void	ft_parent(pid_t *cpid, int nbr_child, int *code) // wait childs
{
	int	i;

	i = 0;
	*code = 0;
	while( i < nbr_child)
	{
		waitpid(cpid[i], code, 0);
		if (cpid[i] == cpid[nbr_child - 1])
		{
			if (*code == SIGINT)
				write(STDERR_FILENO, "\n", 1);
			if (*code == 131)
				write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		}
		i++;
	}
	// if (fd_in != STDIN_FILENO)
	// 	close(fd_in);
	// if (fd_out != STDOUT_FILENO)
	// 	close(fd_out);

	// close fd after ?
	
	// if (WIFEXITED(e_status))
	// 	status = WEXITSTATUS(e_status);
	// else
	// 	status = 1;
	// return (e_status);
}

static void	close_pipefd_on_error(int pipefd[3])
{
	if (pipefd[0] > 0)
		close(pipefd[0]);
	if (pipefd[1] > 0)
		close(pipefd[1]);
	if (pipefd[2] > 0)
		close(pipefd[2]);
}

void ft_cmd(t_group *group, t_main *p, t_list_env *env, int *code)
{
	pid_t	pid;
	char	**new_envp;
	int     cpy_pipefd[3];

	new_envp = get_envp(env);
	// env_destroy_list();
	free_tab(env);
	if (!new_envp)
	{
        ft_putstr_err("error : new_envp");
        *code = 1;
		return ;
	}
	cpy_pipefd[0] = p->pipefd[0];
	cpy_pipefd[1] = p->pipefd[1];
	cpy_pipefd[2] = p->pipefd[2];
	free(p->cpid);
	// free(p); need to ?
	execve(group->cmd[0], group->cmd, new_envp);
	close_pipefd_on_error(cpy_pipefd);
    *code = 1;
	return ;
	// if (open_redir(group, &fd_in, &fd_out))
	// {
	// 	return (free_tab(new_envp), 1);
	// }
	// // pid = fork();
	// if (pid == 0)
	// {
	// 	status = ft_cmd_child(group, new_envp, fd_in, fd_out);
	// 	return (free_tab(new_envp), status);
	// }
	// else if (pid > 0)
	// 	status = ft_cmd_parent(fd_in, fd_out, pid);
	// else
	// {
	// 	free_tab(new_envp);
	// 	return(ft_putstr_err("fork error"), 1);
	// }
	// free_tab(new_envp);
}

int	do_redir(t_group *group, t_main *p, t_list_env *env, int *code)
{
    int new_fd_in;
    int new_fd_out;

    new_fd_in = &p->redir_fd[E_IN];
	new_fd_out = &p->redir_fd[E_OUT];
    if (open_redir(group, &p->redir_fd[E_IN], &p->redir_fd[E_OUT]))
    {
        return (1);
    }
    if (is_built(group->cmd[0]) != 0)
		exec_builtin(group, env, p, code);
	else
		ft_cmd(group, p, env, code);
    if (new_fd_in != &p->redir_fd[E_IN])
	{
		close(new_fd_in);
		dup2(STDIN_FILENO, &p->redir_fd[E_IN]);
	}
    if (new_fd_out != &p->redir_fd[E_OUT])
	{
		close(new_fd_out);
		dup2(STDOUT_FILENO, &p->redir_fd[E_OUT]);
	}
    // if(p)
    //     free_main(p);
    return (*code);
}

// unsigned int	ft_pipeline(t_group *group, t_main *p)
// {

// }


void	exec_child(t_group *group, t_main *p, t_list_env *env, int *code)
{
    if(group->flag_fail == 0)
    {
        if (p->size > 1)
		    ft_pipeline(group, p); //to_replace
        if (do_redir(group, p, env, code)) //to change
            return (free_parsed(p), free_envp_list(env), //replace with destroy
                exit(1)); //fail
        if (is_built(group->cmd[0]) != 0)
            exit(exec_builtin(group, env, p, code)); // to_do_bultin ?
        else
            ft_cmd(group, p, env, code);
    }
	else
        exit(group->flag_fail);
	// if (errno == -1 || errno == ENOENT)
	// 	exit(127);
	// if (errno == EACCES || errno == EISDIR
	// 	|| errno == EPERM || errno == ENOEXEC || errno == EINVAL)
	// 	exit(126);
	//do we use errno ?
    
	// exit(127);
}

static int	ft_dispatch(t_main *p, t_group *group, t_list_env *env, int *code)
{
	int i;
    
    i = 0;
	while (i < p->size)
	{
		if (p->size == 1 && is_built(group->cmd[0]) != 0)
			return (exec_builtin(group, env, p, code)); //or do_builtin
		if (p->size > 1)
			if (pipe(p->pipefd) == -1)
				return (1); // pipe error
		p->cpid[i] = fork();
		if (p->cpid[i] == -1)
			return (close_pipefd(p, false), EXIT_FAILURE);
		if (p->cpid[i] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			exec_child(group, p, env, code); // replace function
		}
		group = group->next;
		i++;
		close_pipefd(p, true);
		p->pipefd[TEMP_READ_END] = p->pipefd[READ_END];
	}
	return (0);
}

static int	cmd_lstsize(t_group *group)
{
	size_t	i;

	i = 0;
	while (group != NULL)
	{
		group = group->next;
		i++;
	}
	return (i);
}

int	init_exec(t_main *p, t_list_env *env)
{
	p->size = cmd_lstsize(p->group);
	p->cpid = (pid_t *)malloc(sizeof(pid_t) * p->size);
	if (!p->cpid)
	{
		free(p);
		return (NULL);
	}
}

void	ft_exec(t_main *p, t_list_env *env, int *code)
{
	t_group *curr;
	// int fd_in;
	// int file_fd;
	// int fd_out;
	// int pipefd[2];
	// char buffer[4096];		//можно ли так делать?
	// ssize_t bytes_read;
	// int e_status;
	// int pipe_res;

	curr = p->group;
	init_exec(p, env);
	int ret_dispatch = ft_dispatch(p, curr, env, code);
	if (p->size == 1 && is_built(curr->cmd[0]) != 0)
    {
        free_parsed(p);
        *code = ret_dispatch;
        return ;
    }
	if (ret_dispatch == 1)
    {
        free_parsed(p);
        *code = 1;
        return ;
    }
	p->redir_fd[E_IN] = get_hd_fd(p, env, code);	// передавать ли fd_in параметром (?)
	if (p->redir_fd[E_IN] != STDIN_FILENO)
		close(p->redir_fd[E_IN]);
	if(p)
		free_parsed(p);
	return (*code);
}
