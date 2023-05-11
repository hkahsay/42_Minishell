#include "../../headers/minishell.h"

char	*skip_spaces(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

int	is_space(char c)
{
	if (c == '\'' || c == '"')
	{
		return (1);
	}
	return (0);
}
