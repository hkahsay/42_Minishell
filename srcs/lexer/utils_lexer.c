
#include "../../headers/minishell.h"

char	*skip_spaces(char *str)
{
    while (*str && ft_isspace(*str))
        str++;
	printf(PURPLE "Spaces skipped\n" RS);
    return(str);  
}

