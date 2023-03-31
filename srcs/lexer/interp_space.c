#include "../../headers/minishell.h"

char	*skip_spaces(char *str)
{
	// char *space;

	// space = " ";
	while (*str && ft_isspace(*str))
		str++;
	// add_token(&head, ft_substr(p, 0, get_wordlen(p)), TOK_WORD);	
	return(str);  
}

int	is_space(char c)
{
	if (c == '\'' || c == '"')
	{
		return (1);
	}
	return (0);
}