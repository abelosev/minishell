#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int is_meta(char **str) //gere tout sauf >> <<
{
	if(**str == '|')
		return (5);
	else if(**str == '>')
	{
		(*str)++;
		if(**str && **str == '>')
		{
			(*str)++;
			return (4);
		}
		else
		{
			// (*str)--;
			return (2);
		}
	}
	else if(**str == '<')
	{
		(*str)++;
		if(**str && **str == '<')
			return (3);
		else
		{
			(*str)--;
			return (1);
		}
	}
	else
		return (0);
}

int main()
{
	int i = 0;
	char *str = "s|fi>le1";
	while(str[i] && (is_meta(&str) != 4))
	{
		i++;
		str++;
	}
	int res = is_meta(&str);
	printf("%d\n", res);
	printf("%d\n", i);
	printf("%s\n", str);
	// printf("%c\n", str[4]);
	return (0);
}