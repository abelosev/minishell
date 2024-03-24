#include "../inc/parsing.h"

int is_alpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int is_digit(char c)
{
    return (c >= '1' && c <= '9');
}

int is_star(char c)
{
    return (c == '*');
}

int is_special_if_bonded(char c)
{
    char s[] = "-$_?0!#";
    int i;

    i = 0;    
    while(s[i])
    {
        if(s[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int no_continue_if_not_bonded(char c)
{
    char s[] = "$0_!><{}[]'\"";
    int i;

    i = 0;    
    while(s[i])
    {
        if(s[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int continue_if_not_bonded(char c)
{
    return (is_alpha(c) == 0 && is_digit(c) == 0 && no_continue_if_not_bonded(c) == 0);
}

//for special char like /@#%~^.,+=-?\ etc WITH is_alpha char before => start from this special char, for $,0,_,! don't

//for special char like /@~^%=+ just after $ => print everything including $

//if this special char 

// special &

char *expand(char *str, t_list_env *list)
{
    char *replace; //create replace instead of print (starting from $)
    char *line1;
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '$' && str[i + 1])
        {
            i++;
            if(is_alpha(str[i]))
            {
                //fonction for searching in env  
                //if nothing found => //a partir de str[i + 1] check for continue_if_not_bonded(str[i])
                //if still not => print \n
            }
            else if(is_digit(str[i]) || is_star(str[i]))
            {
                i++;
                if(str[i])
                    //printf everything left
                else
                    //remove with $
            }
            else if(is_special_if_bonded)
                //fonction for special char
            else
                //print everything including $
        }
        else if(!str[i + 1])
            //print $
        
        //create line1 starting by the beginning of the line again -> stoping before $
        //free str, initialize str by strjoin line1 and replace
    }

    return (str);
}