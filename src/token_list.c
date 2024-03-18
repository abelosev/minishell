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
	node->value = token_tab[i];
	if(ft_strncmp(node->value, "|", 1) == 0)
		node->type = PIPE;
	else if(ft_strncmp(node->value, "<", 1) == 0)
		node->type = REDIR_IN;
	else if(ft_strncmp(node->value, ">", 1) == 0)
		node->type = REDIR_OUT;
	// else if(ft_strncmp(node->value, "<<", 1) == 0)
	// 	node->type = APP_IN;
	// else if(ft_strncmp(node->value, ">>", 1) == 0)
	// 	node->type = APP_OUT;
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

	begin = get_node(token_tab, 0);
	curr = begin;
	i = 1;
	while(token_tab[i] != NULL)
	{
		curr->next = get_node(token_tab, i);
		curr = curr->next;
		i++;
	}
	return (begin);
}