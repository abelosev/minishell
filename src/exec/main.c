#include "../../inc/minishell.h"
#include "../../inc/parsing.h"

unsigned int status = 0;

int	is_exit(char *line)
{
	if(ft_strlen(line) != 4)
		return (1);
	if (ft_strncmp(line, "exit", 4) == 0)
		return (1);
	return (0);
}

// int input_handle(char *line)
// {
// 	if (!line)
//     	return (1);
//     if (is_exit(line) == 0)
//     {
//         free(line);
//         return (1);
//     }
//     if (*line == '\0' || only_spaces(line) || ft_strncmp(line, ":", ft_strlen(line)) == 0
// 		|| ft_strncmp(line, "!", ft_strlen(line)) == 0)
//     {
// 		if(*line != '\0')
//         	free(line);
//         return (2);
//     }
//     return (0);
// }

int main(int argc, char **argv, char **envp)
{	
	char *line;
    t_group *group;
    t_list_env *env;
    t_group *start;
	char **new_env;

	(void)argc;
    (void)argv[0];

	env = get_list(envp);
	while (1)
	{
		line = readline(">$ ");
		if (!line)
		{
			break;
		}
		if (is_exit(line) == 0)
		{
			free(line);
			break;
		}
		if (*line == '\0' || only_spaces(line) || ft_strncmp(line, ":", ft_strlen(line)) == 0 || ft_strncmp(line, "!", ft_strlen(line)) == 0)
		{
			if(ft_strncmp(line, ":", ft_strlen(line)) == 0 || ft_strncmp(line, "!", ft_strlen(line)) == 0)
				add_history(line);
			free(line);
			continue;
		}
		if (line && *line)
			add_history(line);
		group = parser(line, env);
		if (!group)
		{
			status = 1; // ??
			free(line);
			continue;
		}
		// print_group(group);  //parser result if we want to see it
		start = group;
		while(group != NULL)
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
				if(is_built(group->cmd[0]) != 0)
					status = ft_do_builtin(group, env, STDOUT_FILENO);
				else
					status = 0;
			}
			else
			{
				status = group->flag_fail;
			}
			group = group->next;
		}
	}
	free_group_list(start);
	if(line)
		free(line);
	free_envp_list(env);
	clear_history();
	return (status);
}
