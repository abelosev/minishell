#include "../../inc/exec.h"

//doesn't close well when pipe
void	child_pid(t_exec *exec, int *pipe_fd)
{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		dup2(pipe_fd[0], 0); //STDIN_FILENO
		exec->pfd_in = pipe_fd[0];
}
void	parent_pid(t_exec *exec, int *pipe_fd)
{
		waitpid(-1, NULL, 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		dup2(pipe_fd[1], 1); //STDOUT_FILENO
		exec->pfd_out = pipe_fd[1];
}
void		ft_pipe(t_exec *exec)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		//return (1);
		perror("Error ft_pipe");
		return ;
	}
	if (pid == 0)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		dup2(pipe_fd[0], 0); //STDIN_FILENO
		exec->pfd_in = pipe_fd[0];
		exec->pid = -1;
		return ;
		//return (0);
	}
	else
	{
		waitpid(-1, NULL, 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		dup2(pipe_fd[1], 1); //STDOUT_FILENO
		exec->pfd_out = pipe_fd[1];
		exec->pid = pid;
		return ;
		//retuen (0);
	}
}
