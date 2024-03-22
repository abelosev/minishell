#include "../inc/parsing.h"
#include "../inc/minishell.h"

t_group *invalid_group(int flag)
{
	t_group *group;
	group = malloc(sizeof(t_group));
	if(!group || group == NULL) //to remove "group == NULL" ?
	{
		perror("group malloc");
		return (NULL);
	}
	group->flag_fail = flag;
	//free(group);
	group->cmd = NULL;
	group->redir_in = NULL;
	group->redir_out = NULL;
	group->app_out = NULL;
	group->next = NULL;
	return (group);
}

char *outfile_access(t_tokens *list, char *str)
{
	if(str != NULL)
	{
		free(str);
		str = NULL;
	}
	str = ft_strdup(list->next->value);
	if(access(str, F_OK ) != 0)
		return (str);
	else if(access(str, R_OK | W_OK ) != 0)
	{
		printf("Permission denied\n"); //выводить сообщения без printf
		return (NULL);
	}
	return (str);
}

char *infile_access(t_tokens *list, char *str)
{
	if(str != NULL)
	{
		free(str);
		str = NULL;
	}
	str = ft_strdup(list->next->value);
	if(access(str, F_OK) != 0)
	{
		printf("No such file or directory\n");
		return (NULL);
	}
	else if(access(str, R_OK | W_OK ) != 0)
	{
		printf("Permission denied\n");
		return (NULL);
	}
	return (str);
}