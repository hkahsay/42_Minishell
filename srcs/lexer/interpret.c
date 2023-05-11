#include "../../headers/minishell.h"

t_token	*lexer(char *input_str)
{
	char	*p;
	t_token	*head;
	char	*space;
	char	*current;

	head = NULL;
	current = NULL;
	p = input_str;
	space = " ";
	while (p && *p)
	{
		if (ft_isspace(*p))
			add_token(&head, space, TOK_SPACE);
		p = skip_spaces(p);
		if (!*p)
			break ;
		if (is_delim_char(*p))
			check_delim(&p, &head);
		else if (is_quote(*p))
		{
			check_quotes(&p, &head);
			if (*p == '\0')
				return (head);
		}
		else
		{
			while (!ft_isspace(*p))
			{
				current = ft_substr(p, 0, get_wordlen(p));
				add_token(&head, current, TOK_WORD);
				my_free(current);
				p = p + get_wordlen(p);
				break ;
			}
		}
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
	expand_token_list(&token_head, mini_env);
	if (!token_head)
		return ;
	merge_tokens(&token_head);
	delete_tok_spaces(&token_head);
	// printf(GREEN "returned delete_tok_spaces\n" RS);
	if (handle_input_error(&token_head) == 1)
		return ;
	if (token_head)
		parse(&token_head, mini_env);
}
