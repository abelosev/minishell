#include "../inc/parsing.h"
#include "../inc/minishell.h"

int is_alpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int is_digit(char c)
{
    return (c >= '1' && c <= '9');
}

char *copy_before_$(char *str, char c)
{
    size_t	len;
	size_t	i;
    char *copy;

    i = 0;
    len = 0;
    while(str[len] && str[len] != c)
	{
		len++;
	}
	if(str[len + 1] == '\0' || str[len + 1] == ' ' || str[len + 1] == '\t') //for these cases :  1) echo abc$ => abc$ 	2) echo $ => $
		len++;

    copy = malloc(sizeof(char) * (len + 1)); //to check for an eventual unvalid read later
    if(!copy)
        return (NULL);
    while(i < len)
    {
        copy[i] = str[i];
        i++; 
    }
    copy[i] = '\0';
    return (copy);
}

char *expanded_line(char *line, char **envp) //ADD SPACES MANAGEMENT : echo 123$a USER $USER => 123 USER abelosev + 
//if num and not founded in env than we consider only one element after the $ and print all the others + what should we do with '$$' in the middle of line?
//should I define syntaxic errors for expand? + how to manage this : echo $"USER" => USER
{
	char *expanded;
	char *to_search;
	char *new_line;
	t_list_env *start;

	new_line = NULL;
	to_search = NULL;
	expanded = NULL;
    t_list_env *env = get_list(envp);
	start = env;
	// printf("%s not imp\n", env->value);

    new_line = copy_before_$(line, '$');
    printf("before the first $ : %s\n", new_line);

	line = line + ft_strlen(new_line) + 1; //we move the pointer here (to remouve later when you'll manage double pointers)


	while(*line)
	{
		// printf("%c\n", *line);
		if(*line == '_' || is_alpha(*line))
		{
			if(to_search)
			{
				free(to_search);
				to_search = NULL;
			}
			if(expanded)
			{
				free(expanded);
				expanded = NULL;
			}
			to_search = copy_before_$(line, '$');

			env = start;
			while(env != NULL)
			{
				if(ft_strncmp(env->key, to_search, ft_strlen(to_search)) == 0)
				{
					expanded = ft_strdup(env->value);
					printf("expanded part : %s\n", expanded);
					break;
				}
				else
					env = env->next;
			}
			if(expanded)
				new_line = ft_strjoin(new_line, expanded);
		}
		// else if(*line == '?') // IMPORTANT
		// {
		// 	//int status
		// }
		else if(is_digit(*line))
		{
			//no nead to search in env first (in case of EXPORT before) because : export 12a=pff => bash: export: `12a=pff': not a valid identifier
			// MAKE SURE that Meg's export doesn't handle variable names containing numbers

			line++;
			if(to_search)
			{
				free(to_search);
				to_search = NULL;
			}
			if(*line)
			{
				to_search = copy_before_$(line, '$');
				new_line = ft_strjoin(new_line, to_search);
			}
		}
		else
		{
			printf("%s\n", new_line);
			printf("NON GERE\n");
			break;
		}
		if(to_search)
			line = line + ft_strlen(to_search) + 1;
		// if(to_search)
		// 	free(to_search);
	}
	printf("\n\nnew_line : %s\n", new_line);

	return (new_line);  
}