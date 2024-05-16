#include "../../inc/exec.h"

//!! si redir = deja fork
//always connect before I/O redir
//open then dup(2)
//do it for all redir
//exec

//doesn't create all files when multiple redir
//output = last redir output?

// void	redir_in(t_exec *exec, t_group *group)
// {
// 	if (exec->fd_in > 0)
// 		close(exec->fd_in);
// 	exec->fd_in = open(group->redir_in, O_RDONLY | S_IRWXU);
// 	if (exec->fd_in > 0 || dup2(exec->fd_in, 0) == -1)
// 	{
// 		// return (1);
// 		perror("open");
// 		return ;
// 	}
// 	// if (exec->fd_in == -1)
// 	// {
// 	// 	//SIG
// 	// 	perror("open");
// 	// 	return ;
// 	// }
// 	// dup2(exec->fd_in, 0); //STDIN_FILENO
// 	close(exec->fd_in);
// }

// void	redir_out(t_exec *exec, t_group *group)
// {
// 	if (exec->fd_out > 0)
// 		close(exec->fd_out);
// 	exec->fd_out = open(group->redir_out, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
// 	if (exec->fd_out > 0 || dup2(exec->fd_out, 1) == -1)
// 	{
// 		// return (1);
// 		perror("open");
// 		return ;
// 	}
// 	// if (exec->fd_out == -1)
// 	// {
// 	// 	//SIG
// 	// 	perror("open");
// 	// 	return ;
// 	// }
// 	// dup2(exec->fd_out, 1); //STDOUT_FILENO
// 	close(exec->fd_out);
// }

// void	append_out(t_exec *exec, t_group *group)
// {
// 	if (exec->fd_out > 0)
// 		close(exec->fd_out);
// 	exec->fd_out = open(group->app_out, O_APPEND | S_IRWXU);
// 	if (exec->fd_out == -1)
// 	{
// 		//SIG
// 		return ;
// 	}
// 	dup2(exec->fd_out, 1); //STDOUT_FILENO
// 	close(exec->fd_out);
// }

// //last command = first
// //add print group
// void	ft_redir(t_exec *exec, t_group *group)
// {
// 	if (group->redir_in != NULL)
// 		redir_in(exec, group);
// 	else if (group->redir_out != NULL)
// 		redir_out(exec, group);
// 	else if (group->app_out != NULL)
// 		append_out(exec, group);
// 	else
// 		return ;
// 	// if (group->next != NULL)
// 	// {
// 	// 	ft_pipe(exec);
// 	// 	// ft_redir(exec, group, env_lst); //recursive removed
// 	// }
// 	// simple_cmd(exec, group, env_lst);
// }

void	redir_in(t_exec *exec, t_group *group)
{
	if (exec->fd_in > 0)
		close(exec->fd_in);
	exec->fd_in = open(group->redir_in, O_RDONLY | S_IRWXU);
	if (exec->fd_in == -1)
	{
		//SIG
		perror("open");
		return ;
	}
	dup2(exec->fd_in, 0);
	close(exec->fd_in);
}

void	redir_out(t_exec *exec, t_group *group)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->redir_out, \
						O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (exec->fd_out == -1)
	{
		//SIG
		perror("open");
		return ;
	}
	dup2(exec->fd_out, 1);
	close(exec->fd_out);
}

void	append_out(t_exec *exec, t_group *group)
{
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = open(group->app_out, O_APPEND | S_IRWXU);
	if (exec->fd_out == -1)
	{
		//SIG
		return ;
	}
	dup2(exec->fd_out, 1);
	close(exec->fd_out);
}

void	ft_redir(t_exec *exec, t_group *group)
{
	if (group->redir_in != NULL)
		redir_in(exec, group);
	else if (group->redir_out != NULL)
		redir_out(exec, group);
	else if (group->app_out != NULL)
		append_out(exec, group);
}