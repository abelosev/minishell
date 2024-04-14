#include "../inc/parsing.h"

t_group *parser(char *input, t_list_env *env)
{
	char **token_tab;
	t_tokens *token_list;
	t_group *group;
	char *line;
	
	group = malloc(sizeof(t_group));
	if(!group || group == NULL) //to remove "group == NULL" ?
		return (NULL);

	if(only_spaces(input))
	{
		invalid_group(group, 2);
		return (group);
	}

	// line = ft_expand(input, env);
	// if(line == NULL)
	// 	return(invalid_group(2)); //temporary solution

	// printf("expanded line: %s\n", line); //move after quotes check + check the case when no expand needed + check the case when not founded

	line = quotes_expand(input, env);
	if(line == NULL)
	{
		invalid_group(group, 2); //malloc pb or unclosed quotes
		return (group);
	}

	printf("no quotes + expand: %s\n", line); //do expand

	token_tab = ft_split1(line, 1);
	if(token_tab == NULL)
	{
		free(line);
		free_group_list(group);
		return (NULL); //malloc pb
	}
	
	token_list = lexer(token_tab);
	if(token_list == NULL)
	{
		free(line);
		free_group_list(group);
		free_tab(token_tab); //??
		return (NULL); //malloc pb	
	}

	// printf("Token list:\n");
	// print_token_list(token_list);
	// printf("\n");

	if(syntax_pb(token_list))
	{
		free(line);
		free_tab(token_tab);
		free_tokens(token_list);
		invalid_group(group, 2);
		return (group);
	}
	else
	{
		// free_group_list(group);
		group = get_group_list(token_list, env);
		// free_tokens(token_list); 				надо бы раскомментить
		return (group);
	}
	if(line)
		free(line);
	free_tab(token_tab);
	// return (group);
}