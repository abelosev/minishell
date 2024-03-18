#include "../inc/parsing.h"

void free_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
	{
		free(tab[i]); //нужно ли устанавливать в NULL?
		i++;
	}
	free(tab);
}

void free_group(t_group *lg)
{
	if(lg)
	{
		if(lg->cmd)
			free_tab(lg->cmd);
		// if(lg->source != NULL)
		// 	free(lg->source);
		// if(lg->destination != NULL)
		// 	free(lg->destination);
		free(lg);
	}
}

void free_tokens(t_tokens *list)
{
	t_tokens *tmp;
	while(list != NULL)
	{
		tmp = list->next;
		free(list->value);
		if(list->next)
			free(list->next);
		list = tmp;
	}
}

void free_envp_list(t_list_env *list)
{
	t_list_env *tmp;
	while(list != NULL)
	{
		tmp = list->next;
		free(list->key);
		free(list->value);
		free(list->next);
		list = tmp;
	}
}