#include "../inc/parsing.h"

t_tokens *get_node(char **token_tab, int i)
{
	t_tokens *node;

	node = malloc(sizeof(t_tokens));
	if(!node)
	{
		free_tab(token_tab);
		node = NULL;
	}
	node->value = ft_strdup(token_tab[i]);

	if(ft_strncmp(node->value, "|", ft_strlen(node->value)) == 0)
		node->type = PIPE;
	else if(ft_strncmp(node->value, "<", ft_strlen(node->value)) == 0)
		node->type = REDIR_IN;
	else if(ft_strncmp(node->value, ">", ft_strlen(node->value)) == 0)
		node->type = REDIR_OUT;
	else if(ft_strncmp(node->value, "<<", ft_strlen(node->value)) == 0)
		node->type = APP_IN;
	else if(ft_strncmp(node->value, ">>", ft_strlen(node->value)) == 0)
		node->type = APP_OUT;
	else
		node->type = WORD;
	node->next = NULL;
	return (node);
}

t_tokens *lexer(char **token_tab)
{
	int i;
	t_tokens *begin;
	t_tokens *curr;

	begin = get_node(token_tab, 0); //HERE
	if(!begin)
		return (NULL);
	curr = begin;
	i = 1;
	while(token_tab[i] != NULL)
	{
		curr->next = get_node(token_tab, i); //HERE
		if(!curr->next)
		{
			free_tokens(begin); //is it necessary?
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	return (begin);
}

// int get_tokens_nb(t_tokens *list)
// {
// 	int node_nb;

// 	node_nb = 0;
// 	while(list->type == 0)
// 	{
// 		list = list->next;
// 		node_nb++;
// 	}
// 	return (node_nb);
// }