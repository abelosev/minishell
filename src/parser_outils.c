#include "../inc/parsing.h"

// char **file_access(char **tab)
// {
//     int i;

//     i = 0;
//     char **res = malloc(sizeof(char *) * 2);
//     if(!res)
//         return(NULL); 
//     while(tab[i])
//     {
//         if(access(tab[i], F_OK | R_OK | W_OK ) != 0) //should we remove X_OK ?
//         {
//             free(res);
//             return (NULL);
//         }
//         i++;
//     }
//     res[0] = ft_strdup(tab[i - 1]);
//     res[1] = NULL;
//     return (res);
// }

// /*int main()
// {
//     char **tab = malloc(sizeof(char *) * 4);
//     tab[0] = "file1";
//     tab[1] = "file2";
//     tab[2] = "file3";
//     tab[3] = NULL;

//     char **res = file_access(tab);
//     if(res != NULL)
//     {
//         printf("le vrai output : %s\n", res[0]);
//         free_tab(res);
//     }
//     else
//         printf("No access\n");
//     free(tab);
//     return (0);
// }*/