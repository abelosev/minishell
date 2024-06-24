#include "minishell.h"

void    exec_builtin(t_main *p, t_list_env *env, t_exec *e, int *code)
{
    t_group *group;

    group = p->group;
    *code = ft_do_builtin(group, env, e->fd_out, code);
    if (is_built(group->cmd[0]) == B_EXIT)
	{
        ft_putstr_err("exit\n");
        free_envp_list(env);
        if (p)
            free_main(p);
        if (e->cpid)
            free(e->cpid);
        clear_history();
        exit(*code);
    }
}

void	ft_cmd_child(t_group *group, char **new_envp, t_exec *e)
{
    if (e->fd_in != STDIN_FILENO)
    {
        dup2(e->fd_in, STDIN_FILENO);
        close(e->fd_in);
    }
    if (e->fd_out != STDOUT_FILENO)
    {
        dup2(e->fd_out, STDOUT_FILENO);
        close(e->fd_out);
    }
    execve(group->cmd[0], group->cmd, new_envp);
}

void	ft_cmd(t_group *group, t_list_env *env, t_exec *e, int *code)
{
    pid_t   pid;
    char    **new_envp;

    new_envp = get_envp(env);
    if (!new_envp)
    {
        *code = 1;
        return ;
    }
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, ft_sigint);          //???
        signal(SIGQUIT, ft_sigquit);
        ft_cmd_child(group, new_envp, e);
    }
    else if (pid > 0)
	{
		if (e->fd_in != STDIN_FILENO)
        	close(e->fd_in);
		if (e->fd_out != STDOUT_FILENO)
			close(e->fd_out);
	}
    else
        *code = 1;
    free_tab(new_envp);
    e->cpid[e->cpid_index] = pid;
    e->last_pid = pid;
    // if(g_status != 0)                    //???
    //     *code = g_status;
}
