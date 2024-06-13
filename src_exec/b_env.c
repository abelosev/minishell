
//New

#include "../../inc/minishell.h"

int ft_env(t_group *group, t_list_env *env, int fd)
{
	if (group->cmd[1] != NULL)
	{
		write(2, "env: warning: additional arguments to env are ignored\n", 54);
		return (127); //точно ли 127 ?
	}
	print_list(env);
}


//Megan

#include "../../inc/exec.h"
#include "../../inc/minishell.h"

int	builtin_env(t_group *group, t_list_env **env_lst)
{
	if (tab_size(group->cmd) > 1)
	{
		if (ft_strcmp(group->cmd[1], "env") != 0)
			return (2);
	}
	// if (ft_strncmp(group->cmd[0], "env", 3) == 0)
	print_env_list(*env_lst, fd);
	return (0);
}


//Ael

#include "minishell.h"

int	ft_env(char **args, t_env *env, int fd)
{
	t_env	*p;

	p = env;
	if (args[1] != NULL)
	{
		write(2, "env: warning: additional arguments to env are ignored\n", 54);
		return (127);
	}
	while (p)
	{
		if (ft_str_contains_char(p->line, '='))
		{
			write(fd, p->line, ft_strlen(p->line));
			write(fd, "\n", 1);
		}
		p = p->next;
	}
	return (0);
}


int	ft_str_contains_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

