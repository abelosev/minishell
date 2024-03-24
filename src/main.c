#include "../inc/minishell.h"
#include "../inc/parsing.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_group *group;
	t_group *start;

	(void)ac;
	(void)av[0];

	//obtenir t_env_list envp + changer $SHLVL

	line = readline(">$ ");
	while (1)
	{
		if (line && *line)
			add_history(line);
		
		group = parser(line, envp); //group_list is here

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
		free_group_list(start);
		if(line)
			free(line); //do we really need it? (recheck with no other leaks)
		line = readline(">$ ");
	}
	return 0;
}