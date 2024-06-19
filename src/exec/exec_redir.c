#include "minishell.h"

int	is_redir(t_group *group)
{
    return (group->redir_in || group->redir_out || group->app_out);
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

void	do_redir(t_group *group, t_main *p, t_list_env *env, int fd_in, int fd_out, int *code)
{
    int	new_fd_in;
    int	new_fd_out;
    
    new_fd_in = fd_in;
	new_fd_out = fd_out;
    if (open_redir(group, &new_fd_in, &new_fd_out))
    {
        *code = 1;
        return;
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
}

