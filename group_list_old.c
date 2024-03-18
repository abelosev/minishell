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
	group->app_in = NULL;
	group->next = NULL;
	return (group);
}

int get_group_nb(t_tokens *list) //если тут использовать list, то в основной функции он тоже будет в конце? + 
//what will hapen for this type of line: "echo abc > file1 |" (to treat this as a syntax error before?)
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

//заполнение cmd, if the group starts with the cmd name

char *get_cmd_tab(t_tokens *list, t_group *group) //could we progressively fill the group members by different functions?
{
	// t_tokens *curr;
	// int len;
	// int i;
	
	// curr = list;
	// curr->type = list->type;
	// curr->value = ft_strdup(list->value);
	// //printf("curr->value : %s", curr->value);
	// curr->next = list->next; //should we put it here?
	// len = 0;
	// i = 0;
	// while(curr->type == 0 && curr != NULL)
	// {
	// 	len++;
	// 	curr = curr->next;
	// }

	int len;
	int i;
	t_tokens *start;

	len = 0;
	i = 0;
	start = list;
	while(list->type == 0 && list != NULL)
	{
		len++;
		list = list->next;
	}
	group->cmd = malloc(sizeof(char *) * (len + 1));
	if(!group->cmd)
		return (NULL);
	list = start;
	printf("list->value after restart : %s\n", list->value);
	while(i <= len && list != NULL)
	{
		group->cmd[i] = ft_strdup(list->value);
		i++;
		list = list->next;
	}
	group->cmd[i] = NULL;
	// group->redir_in = NULL;
	// group->redir_out = NULL;
	// group->app_in = NULL;
	// group->next = NULL;
	return (group->cmd);
}

char *file_access(t_tokens *list, char *str)
{
	if(str != NULL)
	{
		free(str);
		str = NULL;
	}
	str = ft_strdup(list->next->value);
	if(access(str, F_OK | R_OK | W_OK ) != 0)
	{
		printf("%s: Permission denied\n", str);
		return (NULL);
	}
	return (str);
}



// t_group *get_group(t_tokens *list)
// {
// 	t_group *group;
// 	t_tokens *start;
// 	int len;
// 	int i;

// 	i = 0;
// 	len = 0;
// 	group = malloc(sizeof(t_group));
// 	if(!group)
// 	{
// 		perror("group malloc");
// 		return (NULL); 				//malloc pb
// 	}
// 	start = list;
// 	while(list->type != 5 && list->next->next != NULL)
// 	{
// 		if(list->type != 0 && list->next->type == 0 && list->next->next->type == 0 && group->cmd == NULL) //&& ???
// 		{
// 			list = list->next->next;
// 			group = get_cmd_tab(list, group);
// 		}
// 		list = list->next;
// 	}
// 	list = start;
// 	while(list->type != 5 && list->next->next != NULL)
// 	{
// 		if (list->type == 1  && list->next->type == 0)
// 		{
// 			group->redir_in = ft_strdup(list->next->value);
// 			group->redir_in = file_access(list, group->redir_in);
// 			if(group->redir_in == NULL)
// 				return (invalid_group(1));
// 		}
// 		else if (list->type == 2  && list->next->type == 0)
// 		{
// 			group->redir_out = ft_strdup(list->next->value);
// 			group->redir_out = file_access(list, group->redir_out);
// 			if(group->redir_out == NULL)
// 				return (invalid_group(1));
// 		}
// 		else if (list->type == 4  && list->next->type == 0)
// 		{
// 			group->app_in = ft_strdup(list->next->value);
// 			group->app_in = file_access(list, group->app_in);
// 			if(group->app_in == NULL)
// 				return (invalid_group(1));
// 		}
// 		list = list->next;
// 	}
// 	group->flag_fail = 0;
// 	group->next = NULL;
// 	return (group);
// }

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

//get_group_list

t_group *get_group_list(t_tokens *list)
{
	int nb;
	t_group *begin_gr;
	t_group *curr_gr;

	begin_gr = malloc(sizeof(t_group));
	if(!begin_gr)
		return (NULL); //malloc pb

	// если строка начинается с WORD (то есть с команды)
	if(list->type == 0)
	{
		begin_gr->cmd = get_cmd_tab(list, begin_gr); //list is on the next element

		while(list->type != 5 && list->next != NULL)
		{
			if (list->type == 1  && list->next->type == 0)
			{
				begin_gr->redir_in = ft_strdup(list->next->value);
				begin_gr->redir_in = file_access(list, begin_gr->redir_in);
				if(begin_gr->redir_in == NULL)
					return (invalid_group(1));
			}
			else if (list->type == 2  && list->next->type == 0)
			{
				begin_gr->redir_out = ft_strdup(list->next->value);
				begin_gr->redir_out = file_access(list, begin_gr->redir_out);
				if(begin_gr->redir_out == NULL)
					return (invalid_group(1));
			}
			else if (list->type == 4  && list->next->type == 0)
			{
				begin_gr->app_in = ft_strdup(list->next->value);
				begin_gr->app_in = file_access(list, begin_gr->app_in);
				if(begin_gr->app_in == NULL)
					return (invalid_group(1));
			}
			list = list->next;
		}
	}
	begin_gr->flag_fail = 0;
	begin_gr->next = NULL;

	curr_gr = begin_gr;
	nb = 1;
	while( nb <= get_group_nb(list) && move_after_pipe(list))
	{
		list = move_after_pipe(list);
		if(list->type == 0)
			curr_gr = get_cmd_tab(list, curr_gr);
		curr_gr = get_group(list);
		curr_gr->next = malloc(sizeof(t_group));
		if(!curr_gr)
		return (NULL); //malloc pb
		curr_gr = curr_gr->next;
		nb++;
	}
	return (begin_gr);
}


// t_group *get_group(t_tokens *list, char **envp)
// {
// 	t_group *group;

// 	group = malloc(sizeof(t_group));
// 	if(!group)
// 	{
// 		perror("group malloc");
// 		return (NULL); 				//malloc pb
// 	}
// 	group->cmd = get_tab(list);
// 	if(!group->cmd)
// 	{
// 		perror("malloc problem");
// 		return (NULL);
// 	}
// 	if(is_built(group->cmd[0]) == 0)
// 	{
// 		group->cmd[0] = cmd_check(group->cmd, envp);
// 		if(group->cmd[0] == NULL)
// 		{
// 			free(group);
// 			return (invalid_group(127)); //cmd not found
// 		}
// 	}
// 	group->flag_fail = 0;
// 	group->next = NULL;
// 	return (group);
// }