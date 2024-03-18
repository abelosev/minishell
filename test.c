#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *clean_builtin(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	i--;
	while(str[i] != '/')
		i--;
	i++;
	str = str + i;
	return (str);
}

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

int main(int ac, char **av)
{
    (void)ac;
    //printf("%d\n", quotes_ok(av[1]));
	printf("%s\n", clean_builtin(av[1]));
    return 0;
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

int quotes_ok(char *str) //plus court
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