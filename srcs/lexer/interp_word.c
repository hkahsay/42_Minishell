
#include "../../headers/minishell.h"

char	*skip_spaces(char *str)
{
    while (*str && ft_isspace(*str))
        str++;
	printf(PURPLE "Spaces skipped\n" RS);
    return(str);  
}

int	get_wordlen(char *p)
{
	int	len;
	
	len = 0;
	while (p && *p) //important order
	{
		if (ft_isspace(*p) || *p == '>' || *p == '<' || *p == '|' || is_quote(*p))
			return (len);
		len++;
		p++;
	}
	return (len);
}
