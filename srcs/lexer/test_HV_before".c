#include "../../headers/minishell.h"

char    *skip_spaces(char *str)
{
    while (*str && ft_isspace(*str))
        str++;
	printf(PURPLE "Spaces skipped\n" RS);
    return(str);  
}

static t_token *new_token(char *content, t_toktype type)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->content = ft_strdup(content);
    printf("new_token->content: %s\n", new_token->content);
    new_token->id = type;
    printf("new_token->id: %d\n", new_token->id);
    new_token->next = NULL;
    return (new_token);
}

void add_token(t_token **head, char *content, t_toktype type)
{
    t_token *token = new_token(content, type);

	// if (!token)
	// 	return (0);
    if (*head == NULL)
    {
        *head = token;
    }
    else
    {
		t_token *current = *head;
		while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = token;
    }
}

static int	get_wordlen(char *p)
{
	int	len;
	
	len = 0;
	while (p && *p) //important order
	{
		if (ft_isspace(*p) || *p == '>' || *p == '<' || *p == '|')
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

static int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

static char *check_delim(char **p, t_token **head) //t_delim *delim, 
{
	t_delim *delim;
    unsigned long i = 0;
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
		if (is_special_char(*p)) //*p == '>' || *p == '<' || *p == '|'
		{
			check_delim(&p, &head);
			printf(GREEN "str p: %s\n" RS, p);	
		}
		else
		{
			while (!ft_isspace(*p))
			{
				// printf(LBLUE "ft_strlen(p): %zu\n" RS, ft_strlen(p));
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


      
