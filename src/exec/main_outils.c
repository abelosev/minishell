#include "../../inc/minishell.h"
#include "../../inc/parsing.h"

t_list_env	*get_mini_env()
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

char	*get_line(void)
{
	char *line;

	rl_catch_signals = 0;
	rl_outstream = stderr;
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = readline (">$ ");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	rl_outstream = stdout;
	if (errno == EINTR)
		status = 128 + SIGINT;
	return (line);
}

int	check_line(char *line)
{
	if (!(*line) || only_spaces(line) || ft_strcmp(line, ":") == 0 || ft_strcmp(line, "!") == 0)
	{
		if(ft_strncmp(line, ":", ft_strlen(line)) == 0 || ft_strncmp(line, "!", ft_strlen(line)) == 0)
			add_history(line);
		free(line);
		status = 0;	// верно ли для ! и : ?  (ПРОВЕРИТЬ ЭТОТ ВЫВОД В ШКОЛЕ)
		return (1);
	}
	return (0);
}

int	check_group(t_parsed *parsed, char *line)
{
	if(!parsed->group || parsed->group->flag_fail == 2)
	{
		status = 2;
		free(line);
		return (1);
	}
	//еще одно условие, проверить
	return(0);
}
