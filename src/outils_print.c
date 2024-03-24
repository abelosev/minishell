#include "../inc/parsing.h"

void ft_putstr_err(char *str)
{
	write(2, str, ft_strlen(str));
}

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
	if(tab == NULL)
		return ;
	while(tab[i] != NULL)
	{
		printf("%s ", tab[i]);
		i++;
	}
	printf("\n");
}

void print_group(t_group *group)
{
	if(group == NULL)
		return ;

	printf("\ncmd: ");
	print_tab(group->cmd);
	printf("flag: %d\n", group->flag_fail);

	printf("fichier redir_in: %s\n", group->redir_in);
	printf("fichier redir_out: %s\n", group->redir_out);
	printf("fichier app_out: %s\n", group->app_out);
}