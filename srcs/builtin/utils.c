#include "../../headers/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') {
            return 0;
        }
        i++;
    }
    return (s1[i] - s2[i]);
}


int count_char(char *str, char c)
{
    int count;

    if (!str)
        return(0);
    count = 0;
    while (*str)
    {
        if (*str == c)
            count++;
        str++;
    }
    return(count); 
}