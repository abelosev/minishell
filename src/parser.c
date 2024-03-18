#include "../inc/parsing.h"

t_group *parser(char *line)
{
	char **token_tab;
	t_tokens *token_list;
	t_tokens *start;
	t_group *group;
	
	if(only_spaces(line))
		return(invalid_group(1)); //is this number ok?

	line = remove_quotes(line);
	if(line == NULL)
		return (invalid_group(1)); //malloc pb or unclosed quotes

	printf("no quotes + expand: %s\n", line); //do expand

	token_tab = ft_split1(line, 1);
	if(token_tab == NULL)
		return (NULL); //malloc pb

	// to check syntax problems here //
		//if(syntax_pb(token_tab) != 0)
			// group = invalid_group(); (bash: syntax error near unexpected token `>>')

	token_list = lexer(token_tab);
	start = token_list;
	if(token_list == NULL)
		return (NULL); //malloc pb
	else
	{
		printf("Token list:\n");
		print_token_list(token_list);
		printf("\n");
		token_list = start;
		group = get_group_list(token_list);
		// print_group(group); //shoudn't work for non-existing cmd
		//free_tokens(list);
	}
	return (group);
}