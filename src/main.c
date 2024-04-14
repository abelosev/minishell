#include "../inc/minishell.h"
#include "../inc/parsing.h"

int	is_exit(char *line)
{
	if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
	{
		free(line);
		return (0);
	}
	else
		return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_group *group;
	t_group *start;
	t_list_env *env;

	(void)ac;
	(void)av[0];

	//obtenir t_env_list envp + changer $SHLVL
	env = get_list(envp);

	line = readline(">$ ");
	while (is_exit(line))
	{
		if (line && *line)
			add_history(line);
		
		group = parser(line, env); //group_list is here

		if(!group) //malloc pb
		{
			if(line)
				free(line);
			exit(EXIT_FAILURE); //to think abt builtin exit application here
		}
		
		start = group;
		
		while(group != NULL) //on parcours la liste de groupes
		{
			if(group->flag_fail == 2 || (group->flag_fail == 127 && group->next == NULL)) //if syntax pb or the last cmd is not found
			{
				//changer global var en fonction de flag_fail
				break; 
			}
			else if(group->flag_fail == 0)
			{
				//exec magic
				//changer global var en fonction de flag_fail
			}
			// printf("\nParsed :\n");
			// print_group(group);
			// printf("\n");
			group = group->next;
		}
		// print_group(start);
		free_group_list(start); //FREE
		free_envp_list(env);
		if(line)
			free(line); //do we really need it? (recheck with no other leaks)
		line = readline(">$ ");
	}
	return 0;
}