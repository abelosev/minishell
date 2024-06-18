/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:20:07 by aauthier          #+#    #+#             */
/*   Updated: 2024/06/18 04:20:18 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	close_pipefd(t_parsed *p, int is_in_loop)
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

// main_builtin
unsigned int	exec_builtin(t_group *group, t_parsed *p, t_list_env *env)
{
	status = ft_do_builtin(group, env, p->redir_fd[E_OUT]);
	if(is_built(group->cmd[0]) == B_EXIT)
	{
		ft_putstr_err("exit\n");
		free_envp_list(env);
		if(p)
			free_parsed(p);
		clear_history();
		exit(status);
	}
	return (status);
}

// unsigned int	ft_cmd_child(t_group *group, char **new_envp, int fd_in, int fd_out)
// {
// 	if (fd_in != STDIN_FILENO)
// 	{
// 		dup2(fd_in, STDIN_FILENO);
// 		close(fd_in);
// 	}
// 	if (fd_out != STDOUT_FILENO)
// 	{
// 		dup2(fd_out, STDOUT_FILENO);
// 		close(fd_out);
// 	}
// 	execve(group->cmd[0], group->cmd, new_envp);
// 	return (1);
// }

unsigned int	ft_parent(pid_t *cpid, int nbr_child) // wait childs
{
	int	i;
	int	e_status;

	i = 0;
	e_status = 0;

	while( i < nbr_child)
	{
		waitpid(cpid[i], &e_status, 0);
		if (cpid[i] == cpid[nbr_child - 1])
		{
			if (e_status == SIGINT)
				write(STDERR_FILENO, "\n", 1);
			if (e_status == 131)
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
	return (e_status);
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

unsigned int ft_cmd(t_group *group, t_parsed *p, t_list_env *env)
{
	// pid_t	pid;
	char	**new_envp;
	int		cpy_pipefd[3];

	new_envp = get_envp(env);
	// env_destroy_list();
	if (!new_envp)
	{
		return (ft_putstr_err("error : new_envp"), 1);
	}
	cpy_pipefd[0] = p->pipefd[0];
	cpy_pipefd[1] = p->pipefd[1];
	cpy_pipefd[2] = p->pipefd[2];
	free(p->cpid);
	// free(p); need to ?
	execve(group->cmd[0], group->cmd, new_envp);
	free_tab(new_envp);
	close_pipefd_on_error(cpy_pipefd);
	return (1);
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

int	do_redir(t_group *group, t_parsed *p, t_list_env *env) //to fix the 5 parameters situation
{
	int new_fd_in;
	int new_fd_out;

	new_fd_in = p->redir_fd[E_IN];
	new_fd_out = p->redir_fd[E_OUT];
	if (open_redir(group, &new_fd_in, &new_fd_out))
	{
		return (1);
	}
	if (is_built(group->cmd[0]) != 0)
		status = exec_builtin(group, env, p);
	else
		status = ft_cmd(group, p, env);
	if (new_fd_in != p->redir_fd[E_IN])
	{
		close(new_fd_in);
		dup2(STDIN_FILENO, p->redir_fd[E_IN]);
	}
	if (new_fd_out != p->redir_fd[E_OUT])
	{
		close(new_fd_out);
		dup2(STDOUT_FILENO, p->redir_fd[E_OUT]);
	}
	// if(p)
	//     free_parsed(p);
	return (status);
}

void	no_redir(t_group *group, t_parsed *p)
{
	if (p->group_id == 0)
	{
		if(p->pipefd[TEMP_READ_END] > -1)
			close(p->pipefd[TEMP_READ_END]);
	}
	else
		if (dup2(p->pipefd[TEMP_READ_END], STDIN_FILENO) < 0)
			exit(1);
	if (group->next)
		if (dup2(p->pipefd[WRITE_END], STDOUT_FILENO) < 0)
			exit(1);
	if (p->pipefd[READ_END] > -1)
		close(p->pipefd[READ_END]);
}

void	ft_pipeline(t_group *group, t_parsed *p)
{
	if (!is_redir(group))
		no_redir(group, p);
	else if (group->redir_in)
	{
		if (dup2(p->pipefd[WRITE_END], STDOUT_FILENO) < 0)
			exit(1);
		if (p->pipefd[READ_END] > -1)
			close(p->pipefd[READ_END]);
	}
	else if (group->app_out|| group->redir_out)
	{
		if (dup2(p->pipefd[TEMP_READ_END], STDIN_FILENO) < 0)
			exit(1);
		if (p->pipefd[READ_END] > -1)
			close(p->pipefd[READ_END]);
		if (p->pipefd[WRITE_END] > -1)
			close(p->pipefd[WRITE_END]);
	}
}

void	exec_child(t_group *group, t_parsed *p, t_list_env *env)
{
	if (p->size > 1)
		ft_pipeline(group, p);
	if (do_redir(group, p, env)) //to check
		return (free_parsed(p), free_envp_list(env), exit(1));
	if (is_built(group->cmd[0]) != 0)
		exit(exec_builtin(group, p, env)); // to_do_bultin ?
	else
		ft_cmd(group, p, env);
	// if (errno == -1 || errno == ENOENT)
	// 	exit(127);
	// if (errno == EACCES || errno == EISDIR
	// 	|| errno == EPERM || errno == ENOEXEC || errno == EINVAL)
	// 	exit(126);
	//do we use errno ?
	exit(127);
}

static int	ft_dispatch(t_parsed *p, t_group *group, t_list_env *env)
{
	while (p->group_id < p->size)
	{
		if (p->size == 1 && is_built(group->cmd[0]) != 0)
			return (exec_builtin(group, env, p)); //or do_builtin
		if (p->size > 1)
			if (pipe(p->pipefd) == -1)
				return (1); // pipe error
		p->cpid[p->group_id] = fork();
		if (p->cpid[p->group_id] == -1)
			return (close_pipefd(p, 0), 1);
		if (p->cpid[p->group_id] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			exec_child(group, p, env); // replace function
		}
		group = group->next;
		p->group_id++;
		close_pipefd(p, 1);
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

int	init_exec(t_parsed *p, t_list_env *env)
{
	p->size = cmd_lstsize(p->group);
	p->cpid = (pid_t *)malloc(sizeof(pid_t) * p->size);
	if (!p->cpid)
	{
		free(p);
		return (NULL);
	}
}

unsigned int	ft_exec(t_parsed *p, t_list_env *env)
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
	int ret_dispatch = ft_dispatch(p, curr, env);
	if (p->size == 1 && is_built(curr->cmd[0]) != 0)
		return (free_parsed(p), ret_dispatch);
	if (ret_dispatch == 1)
		return (free_parsed(p), 1);
	p->redir_fd[E_IN] = get_hd_fd(p, env);	// передавать ли fd_in параметром (?)

	if (p->redir_fd[E_IN] != STDIN_FILENO)
		close(p->redir_fd[E_IN]);
	if(p)
		free_parsed(p);
	return (status);

	// pipe_res = 0;
	// while (curr)
	// {
	// 	if (curr->next)
	// 	{
	// 		pipe_res = pipe(pipefd);
	// 		if (pipe_res == -1)
	// 		{
	// 			if(p)
	// 				free_parsed(p);
	// 			return (ft_putstr_err("pipe failed"), 1); // не удалось открыть пайп
	// 		}
	// 	}

	// 	if (curr->flag_fail == 0 && curr->cmd && *(curr->cmd))
	// 	{
	// 		if (is_redir(curr))
	// 		{
	// 			if(open_redir(curr, &fd_in, &fd_out) || fd_out < 0)
	// 			{
	// 				if(p)
	// 					free_parsed(p);
	// 				return (ft_putstr_err("open output failed"), 1);
	// 			}
	// 			status = do_redir(curr, p, env, fd_in, fd_out);
	// 			close(fd_out);
	// 			if (curr->next)
	// 			{
	// 				file_fd = open(curr->redir_out, O_RDONLY);
	// 				if (file_fd < 0)
	// 				{
	// 					if(p)
	// 						free_parsed(p);
	// 					return (ft_putstr_err("open output file failed"), 1);
	// 				}
	// 				while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0)
	// 					write(pipefd[1], buffer, bytes_read);
	// 				close(file_fd);
	// 				close(pipefd[1]);
	// 				fd_in = pipefd[0];
	// 			}
	// 		}
	// 		else
	// 		{
	// 			if (is_built(curr->cmd[0]) != 0)
	// 			{
	// 				if (curr->next)
	// 					status = exec_builtin(curr, env, p, pipefd[1]);
	// 				else
	// 					status = exec_builtin(curr, env, p, STDOUT_FILENO);
	// 			}
	// 			else
	// 			{
	// 				if (curr->next)
	// 					status = ft_cmd(curr, env, fd_in, pipefd[1]);
	// 				else
	// 					status = ft_cmd(curr, env, fd_in, STDOUT_FILENO);
	// 			}
	// 		}
	// 	}
	// 	else
	// 		status = curr->flag_fail;

	// 	if (fd_in != STDIN_FILENO)
	// 		close(fd_in);
	// 	if (pipe_res != 0 && pipefd[1] != STDOUT_FILENO)
	// 		close(pipefd[1]);
	// 	if (curr->next)
	// 		fd_in = pipefd[0];
	// 	curr = curr->next;
	// }
}
