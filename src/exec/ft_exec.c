#include "../../inc/minishell.h"

int	is_redir(t_group *group)
{
	if(group->redir_in)
		return (E_REDIR_IN);
	else if(group->redir_out)
		return (E_REDIR_OUT);
	else if(group->app_in)
		return (E_HD);
	else if(group->app_out)
		return (E_APP_OUT);
	return (0);
}

int	ft_stand_cmd(t_group *group, t_list_env *env)
{
	int pid;
	int exec_stat;
	char **new_envp;

	pid = fork();
	if (pid == 0)
	{
		new_envp = get_envp(env);
		execve(group->cmd[0], group->cmd, new_envp);
		perror("execve");
		free(new_envp);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &exec_stat, 0);  // Wait for child process to finish
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


//добавить обработку сигналов внутри

int	ft_exec(t_group *group, t_list_env *env) //the funct return 0 if it is not a simple cmd to be done and status reflects les changements de la globale
{
	if (group->next == NULL && group->flag_fail == 0 && group->cmd && !is_redir(group))		//if group->cmd exists it has an absolute path to a real cmd
	{
		if(is_built(group->cmd[0]) != 0)		//do builtin
		{
			status = ft_do_builtin(group, env, STDOUT_FILENO);
			if(is_built(group->cmd[0]) == B_EXIT)
			{
				free_envp_list(env);
				free_group_list(group);
				clear_history();
				exit(status);
			}
		}
		else									//do a standard cmd
			status = ft_stand_cmd(group, env);
	}
	else if(group->next == NULL && group->flag_fail != 0)
		status = group->flag_fail;
	return (status);
}