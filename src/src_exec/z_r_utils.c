#include "../../inc/exec.h"

void redir_in_b(t_exec *exec, t_group *group, t_built *fd)
{
    if (exec->fd_in > 0 && exec->fd_in != STDIN_FILENO)
        close(exec->fd_in);
    exec->fd_in = open(group->redir_in, O_RDONLY);
    if (exec->fd_in == -1)
    {
        perror("Error opening input redirection file");
        exit(EXIT_FAILURE);
    }
    fd->in = exec->fd_in;
}

void redir_out_b(t_exec *exec, t_group *group, t_built *fd)
{
    if (exec->fd_out > 0 && exec->fd_out != STDOUT_FILENO)
        close(exec->fd_out);
    exec->fd_out = open(group->redir_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (exec->fd_out == -1)
    {
        perror("Error opening output redirection file");
        exit(EXIT_FAILURE);
    }
    fd->out = exec->fd_out;
}

void append_out_b(t_exec *exec, t_group *group, t_built *fd)
{
    if (exec->fd_out > 0 && exec->fd_out != STDOUT_FILENO)
        close(exec->fd_out);
    exec->fd_out = open(group->app_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (exec->fd_out == -1)
    {
        perror("Error opening append redirection file");
        exit(EXIT_FAILURE);
    }
    fd->out = exec->fd_out;
}

void ft_redir_b(t_exec *exec, t_group *group, t_built *fd)
{
    if (group->redir_in != NULL)
        redir_in_b(exec, group, fd);
    if (group->redir_out != NULL)
        redir_out_b(exec, group, fd);
    if (group->app_out != NULL)
        append_out_b(exec, group, fd);
}
