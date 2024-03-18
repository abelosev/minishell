#include "../inc/parsing.h"

void print_list(t_list_env *list)
{
	while(list != NULL)
	{
		printf("%s", list->key);
		printf("=");
		printf("%s\n", list->value);
		list=list->next;
	}
}

void print_token_list(t_tokens *list)
{
	while(list != NULL)
	{
		printf("%u", list->type);
		printf("=");
		printf("%s\n", list->value);
		list=list->next;
	}
}

void print_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		printf("%s ", tab[i]);
		i++;
	}
	printf("\n");
}

void print_group(t_group *group)
{
	while(group != NULL)
	{
		printf("cmd: ");
		print_tab(group->cmd);
		printf("flag: %d\n", group->flag_fail);
		printf("fichier redir_in: %s\n", group->redir_in);
		printf("fichier redir_out: %s\n", group->redir_out);
		printf("fichier app_out: %s\n", group->app_out);
		group = group->next;
	}
}