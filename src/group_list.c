#include "../inc/parsing.h"
#include "../inc/minishell.h"

int get_group_nb(t_tokens *list)
{
    int group_nb;

    group_nb = 1;
    while(list != NULL)
    {
        if(list->type == 5)
            group_nb++;
        list = list->next;
    }
    return (group_nb);
}

char **get_cmd_tab(t_tokens *list) // не обрабатывает cmd из 2 элементов
{
	int len;
	int i;
	t_tokens *start;
    char **cmd_tab;

	len = 0;
	i = 0;
	start = list;
	while(list->type != 0 && list != NULL)
		list = list->next;
	start = list;
	//синтаксические ошибки будут проверяться раньше

	while(list->type == 0 && list != NULL) 
	{
		len++;
		list = list->next;
	}
	// printf("len : %d\n", len);
	cmd_tab = malloc(sizeof(char *) * (len));
	if(!cmd_tab)
		return (NULL);
	list = start;
	// printf("list->value : %s\n", list->value);
	while(i < len && list != NULL)
	{
		cmd_tab[i] = ft_strdup(list->value);
		printf("cmd_tab[%d] : %s\n", i, cmd_tab[i]);
		i++;
		list = list->next;
	}
	cmd_tab[i] = NULL;
    printf("Here is the group->cmd : ");
    print_tab(cmd_tab);
	printf("\n\n");
	return (cmd_tab);
}

t_group *get_files(t_tokens *list, t_group *group)
{
	while(list->type != 5 && list->next != NULL)
	{
		if (list->type == 1  && list->next->type == 0)
			{
				group->redir_in = ft_strdup(list->next->value);
				group->redir_in = infile_access(list, group->redir_in);
				if(group->redir_in == NULL)
					return (invalid_group(1));
			}
			else if (list->type == 2  && list->next->type == 0)
			{
				group->redir_out = ft_strdup(list->next->value);
				group->redir_out = outfile_access(list, group->redir_out);
				if(group->redir_out == NULL)
					return (invalid_group(1));
			}
			else if (list->type == 4  && list->next->type == 0)
			{
				group->app_out = ft_strdup(list->next->value);
				group->app_out = outfile_access(list, group->app_out);
				if(group->app_out == NULL)
					return (invalid_group(1));
			}
			list = list->next->next;
	}
	return (group);
}

t_tokens *move_after_pipe(t_tokens *list) //одна и та же запись?
{
	while(list->type != 5 && list->next != NULL)
		list = list->next;

	if(list->next != NULL)
	{
		list = list->next;
		return (list);
	}
	else
		return (NULL);

	// list = list->next;
	// if(list == NULL)
	// 	return (NULL);
	// else
	// 	return (list);
}

t_group *get_group(t_tokens *list)
{
	t_tokens *start;
	t_group *group;

	start = list;
	group = malloc(sizeof(t_group));
	if(!group)
		return (NULL); //malloc pb
    group = invalid_group(0);
	group->cmd = get_cmd_tab(list);
	list = start;
	group = get_files(list, group);
	return (group);
}

t_group *get_group_list(t_tokens *list)
{
	int nb;
	t_group *begin_gr;
	t_group *curr_gr;

	begin_gr = get_group(list);

    printf("Print first group : \n");
    print_group(begin_gr);
    printf("\n");

    if(get_group_nb(list) == 1)
        return (begin_gr);
    else
    {
        curr_gr = begin_gr;
        curr_gr->cmd = copy_tab(begin_gr->cmd);
		if(curr_gr->app_out)
        	curr_gr->app_out = ft_strdup(begin_gr->app_out);
		if(curr_gr->redir_in)
        	curr_gr->redir_in = ft_strdup(begin_gr->redir_in);
		if(curr_gr->redir_out)
        	curr_gr->redir_out = ft_strdup(begin_gr->redir_out);
        curr_gr->flag_fail = begin_gr->flag_fail;
        curr_gr->next = NULL;

        nb = 2; //???
        while( nb <= get_group_nb(list) && move_after_pipe(list))
        {
            list = move_after_pipe(list);

            if(list == NULL) //должно входить в проверку синтаксиса раньше
                break;
            curr_gr->next = malloc(sizeof(t_group));
			if(!curr_gr->next)
				return (NULL); //malloc pb
			curr_gr = curr_gr->next;
			curr_gr = get_group(list);
			nb++;
		}
    }
	printf("Print group_list : \n");
    print_group(begin_gr);
    printf("\n");
	return (begin_gr);
}