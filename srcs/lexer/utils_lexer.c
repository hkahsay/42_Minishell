
#include "../../headers/minishell.h"

char *epur_str(char *str)
{
    char *result; // allocate memory for the result string
    char *p;
    int space_flag = 0;

	if (!str)
		return (0); // to check what we have to return here
	result = malloc(ft_strlen(str) + 1); // allocate memory for the result string
	if (!result)
		return (0);
	p = result;
    // skip leading spaces
    while (ft_isspace(*str))
		str++;
    // copy string with exactly one space between words
    while (*str != '\0')
	{
		if (ft_isspace(*str))
		{
			if (!space_flag)
			{
				*p++ = ' ';
				space_flag = 1;
			}
        }
		else
		{
			*p++ = *str;
			space_flag = 0;
		}
		str++;
	}
    // remove trailing space
    if (space_flag && p > result)
		 p--;
    // add null terminator
    *p = '\0';
    return (result);
}
