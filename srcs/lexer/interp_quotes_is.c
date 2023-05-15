#include "../../headers/minishell.h"

int	is_q(char c)
{
	if (c == '\'' || c == '"')
	{
		return (1);
	}
	return (0);
}

// eval_quote
int	eqt(char *q)
{
	if (*q == '\"')
		return (T_DQ);
	else if (*q == '\'')
		return (T_SQ);
	return (0);
}
