#include "../../inc/exec.h"

// void	init_std(t_exec *exec)
// {
// 	exec->infile = dup(0); //STDIN_FILENO
// 	exec->outfile = dup(1); //STDOUT_FILENO
// }

// void	reset_std(t_exec *exec)
// {
// 	dup2(exec->infile, 0); //STDIN_FILENO
// 	dup2(exec->outfile, 1); //STDOUT_FILENO
// }

// void	close_std(t_exec *exec)
// {
// 	close(exec->infile);
// 	close(exec->outfile);
// }
// void	init_exec(t_exec *exec)
// {
// 	exec->fd_in = -1;
// 	exec->fd_out = -1;
// 	exec->pfd_in = -1;
// 	exec->pfd_out = -1;
// 	exec->pid = -1;
// }

// void	close_fds(t_exec *exec)
// {
// 	if (exec->fd_in > 0)
// 		close(exec->fd_in);
// 	if (exec->fd_out > 0)
// 		close(exec->fd_out);
// 	if (exec->pfd_in > 0)
// 		close(exec->pfd_in);
// 	if (exec->pfd_out > 0)
// 		close(exec->pfd_out);
// }

void	set_io(t_exec *exec)
{
	dup2(exec->fd_in, 0);
	dup2(exec->fd_out, 1);
}

void	init_exec(t_exec *exec)
{
	exec->status = -1;
	exec->fd_in = -1;
	exec->fd_out = -1;
	exec->pfd_in = -1;
	exec->pfd_out = -1;
	exec->pid = -1;
}

void	close_fds(t_exec *exec)
{
	if (exec->fd_in > 0)
		close(exec->fd_in);
	if (exec->fd_out > 0)
		close(exec->fd_out);
	if (exec->pfd_in > 0)
		close(exec->pfd_in);
	if (exec->pfd_out > 0)
		close(exec->pfd_out);
}