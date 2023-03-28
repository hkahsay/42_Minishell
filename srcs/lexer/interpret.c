#include "../../headers/minishell.h"

t_token    *interp(char *input_str)
{
    char *p;
    t_token *token;
    t_token *head;

    token = NULL;
    head = NULL;
    p = input_str;
    init_token(token);
    while (p && *p)
    {
		p = skip_spaces(p);
		if (!*p)
			break;
		if (is_delim_char(*p))
			check_delim(&p, &head);
		else if (is_quote(*p))
		{
			check_quotes(&p, &head);
			if (*p == '\0')
			{
				print_token(head);
			 	return (head);
			}
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


      
