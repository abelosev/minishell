#include "../../inc/minishell.h"


int	is_redir(t_group *group)
{
	if(group->redir_in)
		return (E_REDIR_IN);
	else if(group->redir_out)
		return (E_REDIR_OUT);
	else if(group->app_out)
		return (E_APP_OUT);
	return (0);
}

int	ft_stand_cmd(t_group *group, t_list_env *env, int fd_in, int fd_out)
{
	int pid;
	int exec_stat;
	char **new_envp;

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
		new_envp = get_envp(env);
		execve(group->cmd[0], group->cmd, new_envp);
		perror("execve");
		free(new_envp);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &exec_stat, 0);
		if (WIFEXITED(exec_stat))
			exec_stat = 0;
		else
			exec_stat = 1;
	}
	else
	{
		perror("fork");
    	exec_stat = 1;
	}
	return (exec_stat);
}


int	ft_exec(t_parsed *p, t_list_env *env) //the funct return 0 if it is not a simple cmd to be done and status reflects les changements de la globale
{
	int	fd_in;
	int fd_out;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;

	fd_in = get_hd_fd(p, env);	//		вызывая hd, предполагаем, что он не зависит от пайпов
	if (p->group->next == NULL && p->group->flag_fail == 0 && p->group->cmd && !is_redir(p->group))		//if group->cmd exists it has an absolute path to a real cmd
	{
		if(is_built(p->group->cmd[0]) != 0)		//do builtin
		{
			status = ft_do_builtin(p->group, env, STDOUT_FILENO);
			if(is_built(p->group->cmd[0]) == B_EXIT)
			{
				free_envp_list(env);
				free_parsed(p);
				clear_history();
				exit(status);
			}
		}
		else									//do a standard cmd
		{
			status = ft_stand_cmd(p->group, env, fd_in, fd_out);
		}
	}
	else if(p->group->next == NULL && p->group->flag_fail != 0)
		status = p->group->flag_fail;

	return (status);
}