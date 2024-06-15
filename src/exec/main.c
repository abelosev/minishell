#include "../../inc/minishell.h"
#include "../../inc/parsing.h"

unsigned int status = 0;

int	exit_minishell(t_list_env *env, char *line, int exit_code)
{
	// ft_putstr_err("exit\n");
	free_envp_list(env);
	if(line)
		free(line);
	clear_history();
	exit(exit_code);
}

int	minishell_loop(t_list_env *env)
{
	char		*line;
    t_parsed	*parsed;

	while (1)
	{
		line = get_line();
		if (!line)
			exit_minishell(env, line, 1);
		if(check_line(line))
			continue ;
		add_history(line);
		parsed = parser(line, env);
		if(!parsed)
			exit_minishell(env, line, 1);
		if(check_group(parsed, line))
			continue ;
		// if(parsed->group)
		// 	print_group_list(parsed->group); // parser result if we want to see it
		// free(line);
		status = ft_exec(parsed, env);
	}
	free_parsed(parsed);
	clear_history();
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_list_env	*new_env;

	if (!argv || argc != 1)
		return (1);
	if (!envp || !envp[0])
		new_env = get_mini_env();
	else
		new_env = get_list(envp);
	if (!new_env)
		return (perror("new_env"), 1);
	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	status = minishell_loop(new_env);
	free_envp_list(new_env);
	return (status);
}
