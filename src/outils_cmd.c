#include "../inc/parsing.h"

int only_spaces(char *str)
{
	// if(!str[0])
	// 	return (1);
	while(*str == ' ')
		str++;
	if(*str == '\0')
		return (1);
	return (0);
}

int    is_built(char *str)
{
    int        i;
    char    *tab[7];

    i = 0;
    tab[0] = "env";
    tab[1] = "pwd";
    tab[2] = "echo";
	tab[3] = "unset";
	tab[4] = "export";
	tab[5] = "cd";
	tab[6] = "exit";
    while (str[i] && i <= 6)
    {
        if (ft_strncmp(str, tab[i], ft_strlen(str)) == 0)
            return (1);
        i++;
    }
    return (0);
}

// char **get_tab(t_tokens *list)
// {
// 	char **tab;
// 	int i;
// 	int len;

// 	i = 0;
// 	len = get_tokens_nb(list) + 1;
// 	tab = malloc(sizeof(char*) * len);
// 	if(!tab)
// 		return (NULL);
// 	while(i < len && list->type == 0)
// 	{
// 		tab[i] = ft_strdup(list->value);
// 		list = list->next;
// 		i++;
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }