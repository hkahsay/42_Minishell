#include "../../headers/minishell.h"

t_token    *lexer(char *input_str)
{
    char *p;
    t_token *token;
    t_token *head;
	char	*space; //*space?

    token = NULL;
    head = NULL;
    p = input_str;
	space = " ";
    init_token(token);
    while (p && *p)
    {
		if (ft_isspace(*p))
			add_token(&head, space, TOK_SPACE);	
		p = skip_spaces(p);
		if (!*p)
			break;
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
				add_token(&head, ft_substr(p, 0, get_wordlen(p)), TOK_WORD);
				p = p + get_wordlen(p);
				break ;
			}
		}
    }
	// print_token(head);
	// parse(head);
    return(head);
}

void interp(char *line, t_envnode *mini_env)
{
	t_token	*token_head;
	// t_token	*token_exp_head;
	// t_token	*token_merge;

	token_head = lexer(line);
	if (!token_head)
		return ;
	print_token(token_head);	
	// t_token	*token_exp_head;	
	// free_token_list(token_head);	
	expand_token_list(&token_head, mini_env); //token_exp_head = 
	if (!token_head)
		return ;
	printf(GREEN "token_head\n" RS);
	print_token(token_head);
	// token_merge = token_exp_head;
	merge_tokens(&token_head);	//token_merge = 
	// free_token_list(token_head);
	delete_tok_spaces(&token_head);
	printf(GREEN "returned delete_tok_spaces\n" RS);
	handle_input_error(&token_head);
	if (token_head)
	{
		parse(&token_head, mini_env); //, mini_env
		// free_token_list(token_head);
	}
	// if (token_exp_head)
	// {
	// 	parse(&token_exp_head);
	// 	free_token_list(token_exp_head);
	// }
}
      
