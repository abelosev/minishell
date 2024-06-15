#include "minishell.h"

typedef struct s_exec {
	int		fd_p[2];
	int		infile_fd;
	int		outfile_fd;
	pid_t	pid1;
	pid_t	pid2;
	t_group *group;
}	t_exec;

void	error_handler(int value)
{
	if (value < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

t_group *one_group_parse(t_group **group, t_list_env *env)
{
	char **new_envp;

	if(!(*group))			//уже стоим в конце
		return (NULL);
	if((*group)->flag_fail != 0)
	{
		status = (*group)->flag_fail;
	}
	else if((*group)->flag_fail == 0 && (*group)->cmd && (*group)->cmd[0])
	{
		if(is_built((*group)->cmd[0]) != 0)
			status = ft_do_builtin(group, env, STDOUT_FILENO);
		else
		{
			new_envp = get_envp(env);
			status = execve((*group)->cmd[0], (*group)->cmd, new_envp);
			free(new_envp);
		}
	}
	else // ">bonjour"
	{
		//status
	}
	//добавить про redir
	(*group) = (*group)->next;
	return (*group);		//сдвинули на следующий node
}

// void	closing_fd(t_pipex p)
// {
// 	close(p.fd_p[0]);
// 	close(p.fd_p[1]);
// }

int exec_magic(t_group *group, t_list_env *env)
{
	
}
