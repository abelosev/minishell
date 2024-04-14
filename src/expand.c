#include "../inc/parsing.h"
#include "../inc/minishell.h"

char *no_null()
{
	char *str;
	str = malloc(sizeof(char) * 2);
	if(!str)
		return (NULL);
	str[0] = 28;
	str[1] = '\0';
	return (str);
}

char *expanded_token(char *str, t_list_env *env) 
{
	char *res;
	
	res = no_null();

	while(env != NULL)
	{
		if(ft_strncmp(env->key, str, ft_strlen(str)) == 0)
		{
			free(res);
			res = ft_strdup(env->value);
			break;
		}
		else
			env = env->next;
	}
	// free(str);
	return (res);
}

void replace_token(char **str, t_list_env *env)
{
	int i;
	char *new;

	i = 0;
	if((*str)[i] != '$')
		new = ft_strdup((*str));
	else if((*str)[i] == '$' && (*str)[i + 1] == '\0')
		new = ft_strdup((*str));
	else
	{
		if((*str)[i + 1] && is_digit((*str)[i + 1]))
		{
			new = no_null();
		}
		else if((*str)[i + 1] && is_alpha((*str)[i + 1]))
		{
			new = expanded_token((*str) + 1, env);
		}
		//else if(str[i + 1] && str[i + 1] == '?')
			//int status
		else
		{
			new = no_null(); //???
		}
	}
	free((*str));
	(*str) = new;
	// free(str);
}

char *from_tab_to_line(char **tab)
{
	int i;
	char *res;
	char *temp;
	
	temp = no_null();
	res = ft_strdup(tab[0]);
	i = 1;
	while(tab[i])
	{
		if(ft_strncmp(tab[i], temp, ft_strlen(tab[i]) != 0))
			res = ft_strjoin(res, tab[i]);
		i++;
	}
	free(temp);
	free_tab(tab);
	return (res);
}
	
char *ft_expand(char *str, t_list_env *env)
{
	char *temp;
	char **token_tab;
	int i;

	temp = temp_tokenizer(str);
	if(!temp)
		return (NULL);
	token_tab = ft_split1(temp, 3);
	if(!token_tab)
		return (NULL);
	
	i = 0;
	while(token_tab[i]) 
	{
		replace_token(token_tab + i, env);
		i++;
	}
	temp = NULL;
	temp = from_tab_to_line(token_tab);
	return(temp);
}