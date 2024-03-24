#include "../inc/parsing.h"

int syntax_pb(t_tokens *list)
{
	if(list->type == 5)
	{
		ft_putstr_err("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while(list != NULL)
	{
		if(list->type >= 1 && list->type <= 4 && list->next != NULL && list->next->type != 0) //to think abt app_in (heredoc)
		{
			ft_putstr_err("minishell: syntax error near unexpected token `");
			ft_putstr_err(list->value);
			ft_putstr_err("'\n");
			return (1);
		}
		if(list->type != 0 && list->next != NULL && list->next->type == 5)
		{
			ft_putstr_err("minishell: syntax error near unexpected token `");
			ft_putstr_err(list->value);
			ft_putstr_err("'\n");
			return (1);
		}
		if(list->type != 0 && list->next == NULL)
		{
			ft_putstr_err("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		list = list->next;
	}
	return (0);
}

t_group *parser(char *input, char **envp)
{
	char **token_tab;
	t_tokens *token_list;
	t_group *group;
	char *line;
	
	if(only_spaces(input))
		return(invalid_group(2)); //is this number ok?

	line = expanded_line(input, envp);
	if(line == NULL)
		return(invalid_group(2)); //temporary solution


	// printf("expanded line: %s\n", line); //move after quotes check + check the case when no expand needed + check the case when not founded

	line = remove_quotes(input);
	if(line == NULL)
	{
		return (invalid_group(2)); //malloc pb or unclosed quotes
	}

	// printf("no quotes + expand: %s\n", line); //do expand

	token_tab = ft_split1(line, 1);
	if(token_tab == NULL)
	{
		free(line);
		return (NULL); //malloc pb
	}
	
	token_list = lexer(token_tab);
	if(token_list == NULL)
	{
		free(line);
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
		// free_tokens(token_list);
		return(invalid_group(2));
	}

	group = get_group_list(token_list, envp);
	if(line)
		free(line);
	// free_tokens(token_list);
	free_tab(token_tab);
	return (group);
}