#include "../../inc/minishell.h"
#include "../../inc/parsing.h"

unsigned int status = 0;

int	minishell_loop(t_list_env *env)
{
	char	*line;
    t_group	*group;

	while (1)
	{
		line = readline (">$ ");
		if (!line)
		{
			//status?
		}
		if (*line == '\0' || only_spaces(line) || ft_strcmp(line, ":") == 0 || ft_strcmp(line, "!") == 0)
		{
			if(ft_strncmp(line, ":", ft_strlen(line)) == 0 || ft_strncmp(line, "!", ft_strlen(line)) == 0)
				add_history(line);
			free(line);
			//status = ??
			continue;
		}
		add_history(line);
		group = parser(line, env);
		if(!group)
		{
			//status (?)
			break ;
		}
		print_group_list(group); //parser result if we want to see it
		if(group->flag_fail == 0 && group->cmd && is_built(group->cmd[0]) != 0)
			status = ft_do_builtin(group, env, STDOUT_FILENO);
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	// int status; //стоит ли отделить эту переменную от глобальной (?)
	t_list_env	*new_env;

	if (!argv || argc != 1)
		return (1);
	if (!envp || !envp[0])
		new_env = get_mini_env();
	else
		new_env = get_list(envp);
	if (!new_env)
		return (1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	status = minishell_loop(new_env);
	free_envp_list(new_env);
	return (status);
}
