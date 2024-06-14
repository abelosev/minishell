#include "minishell.h"
#include "parsing.h"

t_list_env *get_mini_env()
{
	t_list_env	*mini_env;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	mini_env = ft_new_env_node("PWD", cwd);
	if(ft_add_to_msh_env(&mini_env, "SHLVL=1"))
	{
		free(cwd);
		free_envp_list(mini_env);
		return (NULL);
	}
	if(ft_add_to_msh_env(&mini_env, "_=/usr/bin/env"))
	{
		free(cwd);
		free_envp_list(mini_env);
		return (NULL);
	}
	return (mini_env);
}
