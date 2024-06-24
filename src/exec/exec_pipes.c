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

int	create_pipes(int num_pipes, int ***pipes)
{
    int	i;
    
    i = 0;
	*pipes = malloc(sizeof(int *) * num_pipes);
	if (!(*pipes))
		return (1);
    while (i < num_pipes)
    {
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
		{
			free_tab_int(*pipes, i);
			return (1);
		}
        if (pipe((*pipes)[i]) == -1)
        {
            perror("pipe failed");
            return(1);
        }
        i++;
    }
	return (0);
}

void	close_all_pipes(int **pipes, int num_pipes)
{
	int i;

	i = 0;
	while(i < num_pipes)
	{
        close(pipes[i][0]);
        close(pipes[i][1]);
		i++;
    }
	free_tab_int(pipes, num_pipes);
}