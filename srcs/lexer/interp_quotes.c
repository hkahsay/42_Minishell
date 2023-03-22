#include "../../headers/minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
	{
		return (1);
	}
	return (0);
}

int eval_quote_type(char *q)
{
	if (*q == '\"')
		return (1);
	else	
		return (0);
}

char *check_quotes(char **p, t_token **head)
{
	char *ptr_quote;
	int	quote_status;
	int quote_len;

	ptr_quote = *p;
	quote_status = 0;
	quote_len = 0;
	while (ptr_quote && *ptr_quote)
	{
		if (quote_status == CLOSED)
		{
			quote_status = OPEN;
			ptr_quote++;
			quote_len++;
			while (*ptr_quote && (!(is_quote(*ptr_quote)) || ((eval_quote_type(*p)) + (eval_quote_type(ptr_quote))) % 2))
			{
				ptr_quote++;
				quote_len++;
			}
		}
		else if (is_quote(*ptr_quote) && quote_status == OPEN)
		{
			quote_status = CLOSED;
			quote_len++;
			if (((eval_quote_type(*p)) + (eval_quote_type(ptr_quote))) % 2 == 0)
				add_token(head, ft_substr(*p, 0, quote_len), TOK_D_QUOTE);
			else if (!(eval_quote_type(ptr_quote)))
				add_token(head, ft_substr(*p, 0, quote_len), TOK_S_QUOTE);
			*p += quote_len;
			return (*p);
		}
	}
	if (!(is_quote(*ptr_quote)) && quote_status == OPEN && *ptr_quote == '\0')
	{
		add_token(head, ft_substr(*p, 0, (*p - ptr_quote)), TOK_ERRQUOTE);
		*p += quote_len;
		return (*p);
	}
	else
		return (*p);
}