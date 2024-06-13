#include "../../inc/minishell.h"

unsigned int status = 0;

int	is_exit(char *line)
{
	if(ft_strlen(line) != 4)
		return (1);
	if (ft_strncmp(line, "exit", 4) == 0)
		return (1);
	return (0);
}

int input_handle(char *line)
{
	if (!line)
    	return (1);
    if (is_exit(line) == 0)
    {
        free(line);
        return (1);
    }
    if (*line == '\0' || only_spaces(line) || ft_strncmp(line, ":", ft_strlen(line)) == 0
		|| ft_strncmp(line, "!", ft_strlen(line)) == 0)
    {
        free(line);
        return (2);
    }
    return (0)
}

int main(int ac, char **av, char **envp)
{
    char *line;
    t_group *group;
    t_list_env *env;
   //  t_exec exec;
    t_group *start;

    (void)ac;
    (void)av[0];
  //   if (*envp == NULL)
//         env = env_lst_sos();
//     else
//     {
//         // obtenir t_env_list envp + changer $SHLVL
//         env = get_list(envp);
//     }
//     init_exec(&exec);

    while (1)
    {
        line = readline(">$ ");
        if (input_handle(line))
            break;
        else if (input_handle(line) == 2)
            continue;
        if (line && *line)
            add_history(line);
        group = parser(line, env);
        if (!group)
        {
            status = 1; // ??
            free(line);
            continue;
        }

        start = group;
		while(group != NULL) //syntax check (как напечатать сообщение?)
		{
			if(group->flag_fail == 2)
				break ;
			group = group->next;
		}
		if(!group)
			group = start;
		while(group != NULL)
		{
			if(group->flag_fail == 0)
			{
				//exec magic
				//changer global var en fonction du retour de execve
			}
			else
			{
				//changer global var en fonction de flag_fail
			}
			group = group->next;
		}
        free_group_list(start);
        free(line);
    }
    free_envp_list(env);
	//
    clear_history();
    return (status);
}
