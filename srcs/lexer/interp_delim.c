#include "../../headers/minishell.h"

int	is_delim_char(char c)
{
	if ((c == '>' || c == '<' || c == '|'))
		return (1);
	return (0);
}

char *check_delim(char **p, t_token **head)
{
	t_delim *delim;
    unsigned long i = 0;
	t_delim delimiters[] = {
    {">>", 2, TOK_REDIR_OUT_APPEND},
    {"<<", 2, TOK_HEREDOC},
	{">", 1, TOK_REDIR_OUT},
    {"<", 1, TOK_REDIR_IN},
    {"|", 1, TOK_PIPE}
	};

	delim = delimiters;
	while (delim->delim_str && (i < sizeof(delimiters) / sizeof(t_delim)))
	{
		if (**p == *delim->delim_str && (delim->delim_len == 1 || strncmp(*p, delim->delim_str, delim->delim_len) == 0))
		{
			add_token(head, delim->delim_str, delim->delim_type);
			if (ft_strlen(*p) - (size_t)delim->delim_len >= 0)
			{
				*p = *p + (delim->delim_len);
				break;		
			}
			if (is_quote(**p) == 1)
				return (*p);
			else
				break;
		}
		++delim;
		i++;
		if (delim->delim_str == NULL && i < sizeof(delimiters) / sizeof(t_delim))
			break;
	}
	return (*p);
}
