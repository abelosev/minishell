#include "../inc/minishell.h"
#include "../inc/parsing.h"

int	is_exit(const char *line)
{
	if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		return (0);
	else
		return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_group *group;

	(void)ac;
	(void)av[0];
	//$SHLVL
	line = readline(">$ ");
	while (is_exit(line)) //поменять на while(1) ?
	{
		if (line && *line)
			add_history(line);
		
		group = parser(line, envp);
		if(!group)
			exit(EXIT_FAILURE); //malloc pb => разве должен exit??
		if(group->flag_fail != 0)
		{
			free(line);
			line = NULL;
			//менять значение int status в зависимости от flag_fail
		}
		else
		{
			//execve
			printf("Parsed :\n");
    		print_group(group);
    		printf("\n");
		}
		line = readline(">$ ");
	}
	return 0;
}