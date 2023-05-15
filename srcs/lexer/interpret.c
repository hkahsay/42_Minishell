#include "../../headers/minishell.h"

static char	*manage_word(char **cur, t_token **head, char **p)
{
	while (!ft_isspace(**p))
	{
		(*cur) = ft_substr((*p), 0, get_wordlen((*p)));
		add_token(&(*head), (*cur), T_W);
		my_free((*cur));
		(*p) = (*p) + get_wordlen((*p));
		break ;
	}
	return ((*p));
}

static char	*manage_space(char **p, t_token **head)
{
	if (ft_isspace(**p))
		add_token((&(*head)), " ", T_SP);
	(*p) = skip_spaces(*p);
	return ((*p));
}

t_token	*lexer(char *input_str)
{
	char	*p;
	t_token	*head;
	char	*current;

	head = NULL;
	current = NULL;
	p = input_str;
	while (p && *p)
	{
		manage_space(&p, &head);
		if (!*p)
			break ;
		if (is_lim_char(*p))
			check_lim(&p, &head);
		else if (is_q(*p))
		{
			check_quotes(&p, &head);
			if (*p == '\0')
				return (head);
		}
		else
			manage_word(&current, &head, &p);
	}
	return (head);
}

void	interp(char *line, t_envnode *mini_env)
{
	t_token	*token_head;

	token_head = NULL;
	token_head = lexer(line);
	if (!token_head)
		return ;
	exp_toklist(&token_head, mini_env);
	if (!token_head)
		return ;
	merge_tokens(&token_head);
	delete_tok_spaces(&token_head);
	if (handle_input_error(&token_head) == 1)
		return ;
	if (token_head)
		parse(&token_head, mini_env);
}
