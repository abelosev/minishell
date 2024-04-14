#include "../inc/parsing.h"
#include "../inc/minishell.h"

void invalid_group(t_group *group, int flag) //should it be void * ?
{
	group->flag_fail = flag;
	group->cmd = NULL;
	group->redir_in = NULL;
	group->redir_out = NULL;
	group->app_out = NULL;
	group->next = NULL;
}

char *outfile_access(t_tokens *list, char *str)
{
	if(str != NULL)
	{
		free(str);
		str = NULL;
	}
	str = ft_strdup(list->next->value);
	if(!str)
		return (NULL);
	if(access(str, F_OK ) != 0)
		return (str);
	else if(access(str, R_OK | W_OK ) != 0)
	{
		free(str);
		printf("Permission denied\n");
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
	if(!str)
		return (NULL);
	if(access(str, F_OK) != 0)
	{
		free(str);
		printf("No such file or directory\n");
		return (NULL);
	}
	else if(access(str, R_OK | W_OK ) != 0)
	{
		free(str);
		printf("Permission denied\n");
		return (NULL);
	}
	return (str);
}