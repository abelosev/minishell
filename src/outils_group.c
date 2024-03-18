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

