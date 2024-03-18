#include "../inc/minishell.h"
#include "../inc/parsing.h"

int	is_exit(const char *line)
{
	if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		return (0);
	else
		return (1);
}

int	main(int ac, char **av)
{
	char	*line;
	t_group *group;

	(void)ac;
	(void)av[0];
	//$SHLVL
	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		
		group = parser(line);
		if(!group)
			exit(EXIT_FAILURE); //malloc pb
		if(group->flag_fail != 0)
			line = NULL;
		else
		{
			printf("Parsed :\n");
    		print_group(group);
    		printf("\n");
		}
		line = readline(">$ ");
	}
	return 0;
}