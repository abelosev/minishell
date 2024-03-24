#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// char *copy_before(char *str, char c)
// {
//     size_t	len;
// 	size_t	i;
//     char *copy;

//     i = 0;
//     len = 0;
//     while(str[len] && str[len] != c)
//         len++;
//     // printf("%ld\n", len);
//     copy = malloc(sizeof(char) * (len));
//     if(!copy)
//         return (NULL);
//     while(i < len)
//     {
//         copy[i] = str[i];
//         i++; 
//     }
//     copy[i] = '\0';
//     return (copy);
// }


//fix double pointers

char *copy_before(char **str, char c)
{
    size_t	len;
	size_t	i;
    char *copy;

    i = 0;
    len = 0;
    char *start = *str;
    while(**str != '\0' && **str != c)
    {
        len++;
        *str++;
    }
    printf("%ld\n", len);
    copy = malloc(sizeof(char) * (len));
    if(!copy)
        return (NULL);
    *str = start;
    while(i < len)
    {
        copy[i] = **str;
        i++;
        *str++;
    }
    copy[i] = '\0';
    return (copy);
}

int main()
{
    char *s1 = "12345$7689$";
    char *s2 = copy_before(&s1, '$');
    printf("first : %s\n", s2);
    char *s3 = copy_before(&s1, '$');
    printf("second : %s\n", s3);
    return (0);
}