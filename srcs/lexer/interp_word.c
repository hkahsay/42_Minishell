#include "../../headers/minishell.h"

int	get_wordlen(char *p)
{
	int	len;

	len = 0;
	while (p && *p)
	{
		if (ft_isspace(*p) || *p == '>' \
		|| *p == '<' || *p == '|' || is_q(*p))
			return (len);
		len++;
		p++;
	}
	return (len);
}
