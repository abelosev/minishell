#include "../inc/parsing.h"

int is_meta(char **str)
{
	if(**str == '|')
	{
		(*str)++;
		return (5);
	}
	else if(**str == '>')
	{
		(*str)++;
		if(**str && **str == '>')
		{
			(*str)++;
			return (4);
		}
		else
			return (2);
	}
	else if(**str == '<')
	{
		(*str)++;
		if(**str && **str == '<')
		{
			(*str)++;
			return (3);
		}
		else
			return (1);
	}
	else
		return (0);
}

char *quotes_ok(char *str) //faire plus court + подумать, что возвращать
{
	int i;
	int res;
	int start;

	i = 0;
	res = 1;
	while(str[i])
	{
		if(str[i] == '"')
		{
			res = 0;
			start = i;
			while(str[i])
			{
				i++;
				if(str[i] == '"')
				{
					res = 1;
					str[start] = 29;
					str[i] = 31;
					//
					break;
				}

			}
		}
		else if(str[i] == '\'')
		{
			res = 0;
			start = i;
			while(str[i])
			{
				i++;
				if(str[i] == '\'') //don't do expand inside
				{
					res = 1;
					str[start] = 30;
					str[i] = 31;
					break;
				}
			}
		}
		if(str[i])
			i++;
	}
	if(res == 0)
	{
		ft_putstr_err("Invalid syntax: unclosed quotes\n");
		return (NULL); //подумать, как записать это во flag_fail
	}
	else
		return (str);
}

int spaces_nb(char *str)
{
	int counter;
	
	counter = 0;
	while(*str)
	{
		if(is_meta(&str) > 0)
			counter++;
		else
			str++; //как будто тоже можно включить в саму is_meta, но неясно, как изменить тогда
	}
	return (counter * 2);
}

char *add_spaces(char *str)
{
	char *new_str;
	int len;
	int i;
	
	i = 0;
	str = quotes_ok(str);
	if(str == NULL)
		return (NULL);

	len = spaces_nb(str) + ft_strlen(str) + 1;

	new_str = malloc(sizeof(char) * (len + 1));
	if(!new_str)
		return (NULL);

	while(i < len && *str)
	{
		if(*str == 29 || *str == 30)
		{
			while(*str && *str != 31 && i < len)
			{
				new_str[i] = *str;
				str++;
				i++;
			}
			if(*str && i < len)
			{
				new_str[i] = *str;
				str++;
				i++;
			}
		}
		if(*str && (is_meta(&str) > 0) && (i + 2 < len))
		{
			new_str[i] = ' ';
			new_str[i + 1] = *str;
			new_str[i + 2] = ' ';
			i += 3;
		}
		new_str[i] = *str;
		if(i < len)
			i++;
		if(*str)
			str++;
	}
	new_str[i] = '\0';
	// printf("\nNEW_STRING : %s\n", new_str);
	return (new_str);
}

int quotes_nb(char *str, char c)
{
	int nb;

	nb = 0;
	while(*str)
	{
		if(*str == c)
			nb++;
		str++;
	}
	return (nb * 2);
}

char *no_quotes(char *str, char c)
{
	char *new;
	int i;
	int k;
	int len;
	
	i = 0;
	k = 0;
	len = ft_strlen(str) - quotes_nb(str, c) + 1;
	new = malloc(sizeof(char) * len);
	if(!new)
		return NULL; // ??

	while(str[i] && k < len)				//echo "" => ??
	{
		if(str[i] == c)
		{
			i++;
			while(str[i] && str[i] != 31 && k < len)
			{
				new[k] = str[i];
				k++;
				i++;
			}
			if(str[i] && str[i] == 31)
				i++;
		}
		if(str[i] && k < len)
		{
			new[k] = str[i];
			k++;
			i++;
		}
	}
	new[k] = '\0';
	return (new);
}


char *quotes_expand(char *str, t_list_env *env)
{
	// char *first_expand;
	char *no_double; // ??
	char *spaces;
	// char *no_single;


	// first_expand = ft_expand(str, env); //???
	// printf("first_expand : %s\n", first_expand);

	no_double = no_quotes(str, 29);
	printf("no_double : %s\n", no_double);

	spaces = add_spaces(no_double);
	printf("spaces : %s\n", spaces);

	spaces = ft_expand(spaces, env);
	printf("afer expand : %s\n", spaces);

	// no_single = no_quotes(spaces, 30);
	// printf("no_single : %s\n", no_single);

	free(no_double);
	// free(str);

	return(spaces);
}