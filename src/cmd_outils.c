#include "../inc/parsing.h"

int get_tokens_nb(t_tokens *list)
{
	int node_nb;

	node_nb = 0;
	while(list->type == 0)
	{
		list = list->next;
		node_nb++;
	}
	return (node_nb);
}

char **get_tab(t_tokens *list)
{
	char **tab;
	int i;
	int len;

	i = 0;
	len = get_tokens_nb(list) + 1;
	tab = malloc(sizeof(char*) * len);
	if(!tab)
		return (NULL);
	while(i < len && list->type == 0)
	{
		tab[i] = ft_strdup(list->value);
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}