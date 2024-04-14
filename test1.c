#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

int main()
{
	int counter;
	
	counter = 0;
	char *str = "s|fi>>le<<1><<0|";
	while(*str)
	{
		if(is_meta(&str) > 0)
			counter++;
		else
			str++;
		printf("here : %c\n", *str);
	}
	printf("we stopped here : %c\n", *str);
	printf("counter : %d\n", counter);
	return (0);
}