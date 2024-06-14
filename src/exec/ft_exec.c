#include "../../inc/minishell.h"

int	is_redir(t_group *group)
{
	if(group->redir_in)
		return (REDIR_IN);
	else if(group->redir_out)
		return (REDIR_OUT);
	else if(group->app_in)
		return (HD);
	else if(group->app_out)
		return (APP_OUT);
	return (0);
}

//добавить обработку сигналов внутри

int	do_simple_cmd(t_group *group, t_list_env *env) //the funct return 0 if it is not a simple cmd to be done and status reflects les changements de la globale
{
	char **new_envp;

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
		{
			new_envp = get_envp(env);
			status = execve(group->cmd[0], group->cmd, new_envp);
			free(new_envp);
		}
		return (1);
	}
	return (0);
}

int	ft_exec(t_group *group, t_list_env *env)
{
	return(do_simple_cmd(group, env));
}