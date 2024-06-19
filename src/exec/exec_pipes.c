#include "minishell.h"

int	group_nb(t_group *group)
{
    int i;

    i = 0;
    while (group != NULL)
	{
        i++;
        group = group->next;
    }
    return i;
}

void	create_pipes(int num_pipes, int (*pipes)[2])
{
    int	i;
    
    i = 0;
    while (i < num_pipes)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe failed");
            exit(1);
        }
        i++;
    }
}