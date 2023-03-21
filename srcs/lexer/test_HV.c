#include "../../headers/minishell.h"

# define CLOSED 0
# define OPEN 1

int	get_wordlen(char *p)
{
	int	len;
	
	len = 0;
	while (p && *p) //important order
	{
		if (ft_isspace(*p) || *p == '>' || *p == '<' || *p == '|') //|| is_quote(*p)
			return (len);
		// printf(LC "*get_word *word inside loop: %c\n" RS, *p);
		len++;
		p++;
	}
	// printf(LC "*get_word *str after loop: %c\n" RS, *p);
	return (len);
}

// static const char * special_char = "><|\"'";
static int	is_special_char(char c)
{
	if ((c == '>' || c == '<' || c == '|')) // c == '\'' || c == '"'
		return (1);
	return (0);
}

int	is_quote(char c)
{
	int	quote_status = 0;

	if (c == '\'' || c == '"')
	{
		if (quote_status == CLOSED)
		{
			printf(R "1a quote_status closed %d\n" RS, quote_status);
			quote_status = OPEN;
			printf(R "1b quote_status opened %d\n" RS, quote_status);
			return (1);
		}
		if (quote_status == OPEN)
		{
			printf(R "2a quote_status opened %d\n" RS, quote_status);
			quote_status = CLOSED;
			printf(R "2b quote_status %d\n" RS, quote_status);
			return (2);
		}
	}
	return (0);
}

static int eval_quote_type(char *q)
{
	if (*q == '\"')
		return (TOK_DQUOTE);
	else	
		return (TOK_SQUOTE);
}


static char *closing_quote_token(char **p, int	len, t_token **head)
{
	add_token(head, ft_substr(*p, 0, len), eval_quote_type(*p));
	*p = *p + len; 
	return (*p);
}

static char *get_quote_token(char **p, t_token **head)
{
	t_quote			*quote;
	unsigned long	i = 0;
	char *q = *p;
	int	quote_length = 0;

	t_quote d_s_quote[] = {
    {"\"", 2, TOK_DQUOTE},
    {"\'", 2, TOK_SQUOTE}
	// {NULL, 0, TOK_ERROR} // how is it possible to stop the loop
	};

	quote = d_s_quote;
	printf(LIME "1 Hello get_quote_token\n" RS);
	printf(LIME "1 received *p: %s\n" RS, *p);
	printf(LIME "1 q: %s\n" RS, q);
	while (quote->quote_str && (i < sizeof(d_s_quote) / sizeof(t_quote)))
	{
		printf(YELLOW "2 Hello get_quote_token while loop\n" RS);
		printf(LIME "2 *q: %c\n" RS, *q);
		printf(LIME "2 *quote->quote_str: %c\n" RS, *quote->quote_str);
		if (*q == *quote->quote_str && (quote->quote_len == 2 || strncmp(q, quote->quote_str, quote->quote_len) == 0))
		{
			printf(YELLOW "3 NOW get_quote_token if q = quote_str\n" RS);
			printf(YELLOW "3 *q: %c\n" RS, *q);
			if (is_quote(*q) == 2)
			{
				printf(YELLOW "4 is_quote %c in get_quote_token is %d\n" RS, *q, is_quote(*q));
				return (q);
				// closing_quote_token(*q, **head);
				// quote_length = **p - q;
				// add_token(&head, ft_substr(**p, 0, quote_length), eval_quote_type(q, quote));
				// 	// printf("*p after p + wordlen: %c\n", *p);
				// break ;
			}
		}
		q++;
		i++;
	}
	if (*q == '\0')
		add_token(head, ft_substr(*p, 0, quote_length), TOK_ERRQUOTE);
	return (q);
}


static char *check_delim(char **p, t_token **head) //t_delim *delim, 
{
	t_delim *delim;
    unsigned long i = 0;
	char *ptr_quote = 0;
	t_delim delimiters[] = {
    {">>", 2, TOK_REDIR_OUT_APPEND},
    {"<<", 2, TOK_HEREDOC},
	{">", 1, TOK_REDIR_OUT},
    {"<", 1, TOK_REDIR_IN},
    {"|", 1, TOK_PIPE}
	// {NULL, 0, TOK_ERROR} // how is it possible to stop the loop
	};

	delim = delimiters;
	while (delim->delim_str && (i < sizeof(delimiters) / sizeof(t_delim)))
	{
		if (**p == *delim->delim_str && (delim->delim_len == 1 || strncmp(*p, delim->delim_str, delim->delim_len) == 0))
		{
			add_token(head, delim->delim_str, delim->delim_type);
			// printf(R "delimiter found: %s %d %d\n" RS, delim->delim_str, delim->delim_len, delim->delim_type);
			// printf("Token added\n");
			// printf(YELLOW "ft_strlen(input_str): %zu\n" RS, ft_strlen(input_str));
			// printf(OR "ft_strlen(p): %zu\n" RS, ft_strlen(p));
			if (ft_strlen(*p) - (size_t)delim->delim_len >= 0) //ft_strlen(input_str) - 
			{
				printf(R "ft_strlen(p): %zu\n" RS, ft_strlen(*p));
				// printf("(size_t)delim->delim_len: %zu\n", (size_t)delim->delim_len);
				*p = *p + (delim->delim_len);
				if (is_quote(**p) == 1)
				{
					ptr_quote = *p;
					get_quote_token(&ptr_quote, head);
				}
					
				if (is_quote(*ptr_quote) == 2)
				{
					closing_quote_token(p, (*p - ptr_quote), head);
					// add_token(&head, ft_substr(**p, 0, quote_length), eval_quote_type(q, quote));
					// p = p + get_wordlen(p);
				// printf("*p after p + wordlen: %c\n", *p);
					break ;
				}	
					printf(R "3 str &p and p: %p %c\n" RS, *p, **p);
					// if (strncmp(p, delim->delim_str, delim->delim_len) != 0)
						break;		
				}
			else
			{
				printf(OL "Out of delimiters loop OK\n" RS);
				break;
			}		
		}
		++delim;
		// printf("delimiters[++]: %s %d %d\n", delim->delim_str, delim->delim_len, delim->delim_type);
		i++;
		if (delim->delim_str == NULL && i < sizeof(delimiters) / sizeof(t_delim))
			break;
		// p++;	
	}
	printf(OR "str p: %s\n" RS, *p);
	return (*p);
}

static char *check_quote_word(char **p, t_token **head)
{
	char *ptr_quote;

	ptr_quote = *p;
	printf(BLUE "1 Hello check_quote_word\n" RS);
	printf(BLUE "1 received *p: %s\n" RS, *p);
	printf(BLUE "1 ptr_quote: %s\n" RS, ptr_quote);
	while (ptr_quote && *ptr_quote)
	{
		printf(BLUE "2 *ptr_quote: %c\n" RS, *ptr_quote);
	 	if (is_quote(*ptr_quote) == 1)
		{
			printf(BLUE "3 Hello check is_quote(*ptr_quote) == 1\n" RS);
			get_quote_token(&ptr_quote, head);
			printf(LBLUE "3 Returned from check is_quote(*ptr_quote) == 1\n" RS);
		}
		ptr_quote++;
	 }		
		if (is_quote(*ptr_quote) == 2)
		{
			printf(BLUE "4 Hello check is_quote(*ptr_quote) == 2\n" RS);
			closing_quote_token(p, (*p - ptr_quote), head);
			// add_token(&head, ft_substr(**p, 0, quote_length), eval_quote_type(q, quote));
			// p = p + get_wordlen(p);
		// printf("*p after p + wordlen: %c\n", *p);
			return (*p);
		}
	// 	ptr_quote++;
	// }
	return (*p);
}


t_token    *interp(char *input_str)
{
    char *p;
    t_token *token;
    t_token *head;

    token = NULL;
    head = NULL;
    p = input_str;
    init_token(token);
	// printf("Token init OK\n");
	// printf("p before loop: %s\n", p);
    while (p && *p)
    {
        p = skip_spaces(p);
		// printf(GREEN "str p: %s\n" RS, p);
		if (!*p)
			break;
		printf(GREEN "str p: %s\n" RS, p);
		if (is_special_char(*p)) //*p == '>' || *p == '<' || *p == '|'
		{
			check_delim(&p, &head);
			printf(GREEN "str p: %s\n" RS, p);	
		}
		else
		{
			printf(OR "You are in the word loop\n" RS);
			while (!ft_isspace(*p))
			{
				printf(YELLOW "ft_strlen(p): %zu\n" RS, ft_strlen(p));
				check_quote_word(&p, &head);
				printf(R "Quotes checked OK\n" RS);	
				add_token(&head, ft_substr(p, 0, get_wordlen(p)), TOK_WORD);
				// printf("*p before p + wordlen: %c\n", *p);
				p = p + get_wordlen(p);
				// printf("*p after p + wordlen: %c\n", *p);
					break ;
			}
		}
		printf(NAVY "p before p++: %s\n" RS, p);
		if (p && *p != '\0')
		{
			// p++;
			printf(NAVY "p after p++: %s\n" RS, p);
		}
		else
		{
			print_token(head);
			return (head);
		}// printf("p after p++: %s\n", p);
    }
	print_token(head);
    return(head);
}


      
