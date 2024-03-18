int quotes_ok(char *str) //faire plus court
{
	int i;
	int res;

	i = 0;
	res = 1;
	while(str[i])
	{
		if(str[i] == '"')
		{
			res = 0;
			while(str[i])
			{
				i++;
				if(str[i] == '"')
				{
					res = 1;
					break;
				}
			}
		}
		else if(str[i] == 39)
		{
			res = 0;
			while(str[i])
			{
				i++;
				if(str[i] == 39)
				{
					res = 1;
					break;
				}
			}
		}
		i++;
	}
	return (res);
}


/*void condition_part(int *res, char *str, char c)
{
	*res = 0;
	while(*str)
	{
		str++;
		if(*str == c)
		{
			*res = 1;
			break;
		}
	}
}

int quotes_ok(char *str)
{
	int res;

	res = 1;
	while(*str)
	{

		if(*str == '"')
		{
			condition_part(&res, str, '"');
		}
		else if(*str == 39)
		{
			condition_part(&res, str, 39);
		}
		str++;
	}
	return (res);
}*/

///////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(const char *s)
{
	int i = 0;
	while(s[i] != '\0')
		i++;
	return (i);
}

void free_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strdup(char *s1)
{
	char	*s;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	s = (char*)malloc(sizeof(*s1) * (len + 1));
	if (s == NULL)
		return (NULL);
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void print_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		printf("%s ", tab[i]);
		i++;
	}
	printf("\n");
}

char **file_access(char **tab)
{
    int i;

    i = 0;
    char **res = malloc(sizeof(char *) * 2);
    if(!res)
        return(NULL); 
    while(tab[i])
    {
        if(access(tab[i], F_OK | R_OK | W_OK ) != 0) //should we remove X_OK ?
        {
            free(res);
            return (NULL);
        }
        i++;
    }
    res[0] = ft_strdup(tab[i - 1]);
    res[1] = NULL;
    return (res);
}

int main()
{
    char **tab = malloc(sizeof(char *) * 4);
    tab[0] = "file1";
    tab[1] = "file2";
    tab[2] = "file3";
    tab[3] = NULL;

    char **res = file_access(tab);
    if(res != NULL)
    {
        printf("le vrai output : %s\n", res[0]);
        free_tab(res);
    }
    else
        printf("No access\n");
    free(tab);
    return (0);
}