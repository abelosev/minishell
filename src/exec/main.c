#include "../../inc/minishell.h"
#include "../../inc/parsing.h"

unsigned int status = 0;

int	minishell_loop(t_list_env *env)
{
	char	*line;
    t_group	*group;

	while (1)
	{
		line = get_line();
		if (!line)
		{
			ft_putstr_err("exit\n");
			// free(line);			??
			free_envp_list(env);
			exit(EXIT_FAILURE);
		}
		if(check_line(line))
			continue ;
		add_history(line);
		group = parser(line, env);
		if(check_group(group, line))
			break ;
		// print_group_list(group); // parser result if we want to see it
		status = ft_exec(group, env);
	}
	// update_exit_status(mini, exit_status); -> адаптировать
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
		return (1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	status = minishell_loop(new_env);
	free_envp_list(new_env);
	return (status);
}
