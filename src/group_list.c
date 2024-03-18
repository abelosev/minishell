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

char **get_cmd_tab(t_tokens *list) //stops on the next non-WORD element of the list
{
	int len;
	int i;
	t_tokens *start;
    char **cmd_tab;

	len = 0;
	i = 0;
	start = list;
	while(list->type == 0 && list != NULL)
	{
		len++;
		list = list->next;
	}
	cmd_tab = malloc(sizeof(char *) * (len));
	if(!cmd_tab)
		return (NULL);
	list = start;
	// printf("list->value after restart by searching for cmd: %s\n", list->value);
	while(i < len && list != NULL)
	{
		cmd_tab[i] = ft_strdup(list->value);
		i++;
		list = list->next;
	}
	cmd_tab[i] = NULL;
    // printf("Here is the group->cmd :\n");
    // print_tab(cmd_tab);
	return (cmd_tab);
}

char *file_access(t_tokens *list, char *str)
{
	if(str != NULL)
	{
		free(str);
		str = NULL;
	}
	str = ft_strdup(list->next->value);
	if(access(str, F_OK | R_OK | W_OK ) != 0) //change flags for redir_out and app_out
	{
		printf("Permission denied\n");
		return (NULL);
	}
	return (str);
}

t_tokens *move_after_pipe(t_tokens *list)
{
	while(list->type != 5 && list->next != NULL)
		list = list->next;
	list = list->next;
	if(!list)
		return (NULL);
	else
		return (list);
}

// t_group *get_group(t_tokens *list)
// {
    
// }

t_group *get_group_list(t_tokens *list)
{
	int nb;
	t_group *begin_gr;
	t_group *curr_gr;

	begin_gr = malloc(sizeof(t_group));
	if(!begin_gr)
		return (NULL); //malloc pb
    begin_gr = invalid_group(0);

	// если строка начинается с WORD (то есть с команды)
	if(list->type == 0)
	{
		begin_gr->cmd = copy_tab(get_cmd_tab(list)); //list is on the next element
        printf("In group :\n");
        print_tab(begin_gr->cmd);

		while(list->type != 5 && list->next != NULL)
		{
			if (list->type == 1  && list->next->type == 0)
			{
				// begin_gr->redir_in = ft_strdup(list->next->value);
				begin_gr->redir_in = file_access(list, begin_gr->redir_in);
				if(begin_gr->redir_in == NULL)
					return (invalid_group(1));
			}
			else if (list->type == 2  && list->next->type == 0)
			{
				// begin_gr->redir_out = ft_strdup(list->next->value);
				begin_gr->redir_out = file_access(list, begin_gr->redir_out);
				if(begin_gr->redir_out == NULL)
					return (invalid_group(1));
			}
			else if (list->type == 4  && list->next->type == 0)
			{
				// begin_gr->app_in = ft_strdup(list->next->value);
				begin_gr->app_out = file_access(list, begin_gr->app_out);
				if(begin_gr->app_out == NULL)
					return (invalid_group(1));
			}
			list = list->next->next;
		}
        begin_gr->flag_fail = 0;
	    begin_gr->next = NULL;
	}
    else
    {
        t_tokens *start;
        start = list;
        while(list->type != 5 && list->next->next != NULL)
        {
            if(list->type != 0 && list->next->type == 0 && list->next->next->type == 0)
		    {
			    list = list->next->next;
                printf("here1\n");
			    begin_gr->cmd = copy_tab(get_cmd_tab(list));
                printf("\nIn group :\n");
                print_tab(begin_gr->cmd);
                printf("\nhere2\n");

                list = start;

                while(list->next->type != 5 || list->next != NULL)
                {
                    printf("\nhere3\n");
                    if (list->type == 1  && list->next->type == 0)
                    {
                        // begin_gr->redir_in = ft_strdup(list->next->value);
                        begin_gr->redir_in = file_access(list, begin_gr->redir_in);
                        if(begin_gr->redir_in == NULL)
                            return (invalid_group(1));
                    }
                    if (list->type == 2  && list->next->type == 0)
                    {
                        // begin_gr->redir_out = ft_strdup(list->next->value);
                        begin_gr->redir_out = file_access(list, begin_gr->redir_out);
                        if(begin_gr->redir_out == NULL)
                            return (invalid_group(1));
                    }
                    if (list->type == 4  && list->next->type == 0)
                    {
                        // begin_gr->app_out = ft_strdup(list->next->value);
                        begin_gr->app_out = file_access(list, begin_gr->app_out);
                        if(begin_gr->app_out == NULL)
                            return (invalid_group(1));
                    }
                    list = list->next->next;
                }
		    }
            if(list)
		        list = list->next;
        }
    }

    printf("Print first group : \n");
    print_group(begin_gr);
    printf("\n");

    if(get_group_nb(list) == 1)
        return (begin_gr);
    else
    {
        curr_gr = begin_gr;
        curr_gr->cmd = copy_tab(begin_gr->cmd);
        curr_gr->app_out = ft_strdup(begin_gr->app_out);
        curr_gr->redir_in = ft_strdup(begin_gr->redir_in);
        curr_gr->redir_out = ft_strdup(begin_gr->redir_out);
        curr_gr->flag_fail = begin_gr->flag_fail;
        curr_gr->next = NULL;

        nb = 1;
        while( nb <= get_group_nb(list) && move_after_pipe(list))
        {
            list = move_after_pipe(list);
            if(list == NULL)
                break;
            if(list->type == 0)
            {
                curr_gr->cmd = copy_tab(get_cmd_tab(list)); //list is on the next element

                while(list->type != 5 && list->next != NULL)
                {
                    if (list->type == 1  && list->next->type == 0)
                    {
                        // curr_gr->redir_in = ft_strdup(list->next->value);
                        curr_gr->redir_in = file_access(list, curr_gr->redir_in);
                        if(curr_gr->redir_in == NULL)
                            return (invalid_group(1));
                    }
                    else if (list->type == 2  && list->next->type == 0)
                    {
                        // curr_gr->redir_out = ft_strdup(list->next->value);
                        curr_gr->redir_out = file_access(list, curr_gr->redir_out);
                        if(curr_gr->redir_out == NULL)
                            return (invalid_group(1));
                    }
                    else if (list->type == 4  && list->next->type == 0)
                    {
                        // curr_gr->app_out = ft_strdup(list->next->value);
                        curr_gr->app_out = file_access(list, curr_gr->app_out);
                        if(curr_gr->app_out == NULL)
                            return (invalid_group(1));
                    }
                    list = list->next;
                }
                curr_gr->flag_fail = 0;
                curr_gr->next = NULL;
            }
            else
            {
                t_tokens *start;
                start = list;
                while(list->type != 5 && list->next->next != NULL)
                {
                    if(list->type != 0 && list->next->type == 0 && list->next->next->type == 0)
                    {
                        list = list->next->next;
                        curr_gr->cmd = copy_tab(get_cmd_tab(list));

                        list = start;

                        if (list->type == 1  && list->next->type == 0)
                        {
                            // curr_gr->redir_in = ft_strdup(list->next->value);
                            curr_gr->redir_in = file_access(list, curr_gr->redir_in);
                            if(curr_gr->redir_in == NULL)
                                return (invalid_group(1));
                        }
                        else if (list->type == 2  && list->next->type == 0)
                        {
                            // curr_gr->redir_out = ft_strdup(list->next->value);
                            curr_gr->redir_out = file_access(list, curr_gr->redir_out);
                            if(curr_gr->redir_out == NULL)
                                return (invalid_group(1));
                        }
                        else if (list->type == 4  && list->next->type == 0)
                        {
                            // curr_gr->app_out = ft_strdup(list->next->value);
                            curr_gr->app_out = file_access(list, curr_gr->app_out);
                            if(curr_gr->app_out == NULL)
                                return (invalid_group(1));
                        }
                        list = list->next;
                        }
                        break;
                    }
                    list = list->next;
                }

            curr_gr->next = malloc(sizeof(t_group));
            if(!curr_gr->next)
                return (NULL); //malloc pb
            curr_gr = curr_gr->next;
            // curr_gr = invalid_group(1); is it necessary here (to avoid trash)?
            nb++;
        }
        printf("Print group_list : \n");
        print_group(begin_gr);
        printf("\n");

        return (begin_gr);
    }
	
}