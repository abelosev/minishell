#include "minishell.h"

void	exec_builtin(t_group *group, t_list_env *env, t_main *p, int fd_out, int *code)
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

void	ft_cmd_child(t_group *group, char **new_envp, int fd_in, int fd_out, int *code)
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
    exit(1);
}

void	ft_cmd(t_group *group, t_list_env *env, int fd_in, int fd_out, int *code)
{
    pid_t	pid;

    char **new_envp = get_envp(env);
    if (!new_envp)
    {
        *code = 1;
        return;
    }
    pid = fork();
    if (pid == 0)
        ft_cmd_child(group, new_envp, fd_in, fd_out, code);
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
