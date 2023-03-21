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
	int	len = 0;
	// char *str;

	// str = p;
	// printf(LC "*get_word *str before loop: %c\n" RS, *str);
	while (p && *p) //important order
	{
		if (ft_isspace(*p) || *p == '>' || *p == '<' || *p == '|')
		{
			// printf(R "*get_word I found space or delimiter in word!\n" RS);
			// printf(LC "*get_word *str now loop: %c\n" RS, *str);
			return (len);
		}
		printf(LC "*get_word *word inside loop: %c\n" RS, *p);
		len++;
		p++;
	}
	printf(LC "*get_word *str after loop: %c\n" RS, *p);
	return (len);
}

// static const char * special_char = "><|\"'";
static int	is_special_char(char c)
{
	if ((c == '>' || c == '<' || c == '|')) // || c == '"'
		return (1);
	return (0);
}

static char *check_delim(char *p, t_token **head) //t_delim *delim, 
{
	t_delim *delim;
    unsigned long i = 0;
	t_delim delimiters[] = {
    {">>", 2, TOK_REDIR_OUT_APPEND},
    {"<<", 2, TOK_HEREDOC},
	{">", 1, TOK_REDIR_OUT},
    {"<", 1, TOK_REDIR_IN},
    {"|", 1, TOK_PIPE}
	// {NULL, 0, TOK_ERROR}
	};

	delim = delimiters;
	while (delim->delim_str && (i < sizeof(delimiters) / sizeof(t_delim))) // 
	{
		// i = 0;
		// delim = delimiters;
		// check_delim(p, delim, head);
		if (*p == *delim->delim_str && (delim->delim_len == 1 || strncmp(p, delim->delim_str, delim->delim_len) == 0)) // 
		{
			add_token(head, delim->delim_str, delim->delim_type);
			printf(R "delimiter found: %s %d %d\n" RS, delim->delim_str, delim->delim_len, delim->delim_type);
			printf("Token added\n");
			// printf(YELLOW "ft_strlen(input_str): %zu\n" RS, ft_strlen(input_str));
			printf(OR "ft_strlen(p): %zu\n" RS, ft_strlen(p));
			if (ft_strlen(p) - (size_t)delim->delim_len >= 0) //ft_strlen(input_str) - 
			{
				printf("ft_strlen(p): %zu\n", ft_strlen(p));
				printf("(size_t)delim->delim_len: %zu\n", (size_t)delim->delim_len);
				p = p + (delim->delim_len);
				printf("3 str &p and p: %p %c\n", p, *p);
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
	}
	return (p);
}

t_token    *interp(char *input_str)
{
    char *p;
	// char *word;
    t_token *token;
    t_token *head;
    // t_delim *delim;
    // unsigned long i = 0;
	// t_delim delimiters[] = {
    // {">>", 2, TOK_REDIR_OUT_APPEND},
    // {"<<", 2, TOK_HEREDOC},
	// {">", 1, TOK_REDIR_OUT},
    // {"<", 1, TOK_REDIR_IN},
    // {"|", 1, TOK_PIPE}
	// // {NULL, 0, TOK_ERROR}
	// };

	// delim = (t_delim *) &(delimiters[0]);
	// printf("delimiters[0]: %s %d %d\n", delim->delim_str, delim->delim_len, delim->delim_type);
    token = NULL;
    head = NULL;
    p = input_str;
    init_token(token);
	printf("Token init OK\n");
	printf("p before loop: %s\n", p);
    while (p && *p)
    {
		// i = 0;
		// delim = delimiters;
        p = skip_spaces(p);
		printf(GREEN "str p: %s\n" RS, p);
        if (!*p)
            break;
        // p is not a space nor end of string
		if (is_special_char(*p)) //*p == '>' || *p == '<' || *p == '|'
		{
			check_delim(p, &head); //delim, 
			// while (delim->delim_str && (i < sizeof(delimiters) / sizeof(t_delim))) // 
			// {
			// 	// check_delim(p, delim, head);
			// 	if (*p == *delim->delim_str && (delim->delim_len == 1 || strncmp(p, delim->delim_str, delim->delim_len) == 0)) // 
			// 	{
			// 		add_token(&head, delim->delim_str, delim->delim_type);
			// 		printf(R "delimiter found: %s %d %d\n" RS, delim->delim_str, delim->delim_len, delim->delim_type);
			// 		printf("Token added\n");
			// 		printf(YELLOW "ft_strlen(input_str): %zu\n" RS, ft_strlen(input_str));
			// 		printf(OR "ft_strlen(p): %zu\n" RS, ft_strlen(p));
			// 		if (ft_strlen(p) - (size_t)delim->delim_len >= 0) //ft_strlen(input_str) - 
			// 		{
			// 			printf("ft_strlen(p): %zu\n", ft_strlen(p));
			// 			printf("(size_t)delim->delim_len: %zu\n", (size_t)delim->delim_len);
			// 			p = p + (delim->delim_len);
			// 			printf("3 str &p and p: %p %c\n", p, *p);
			// 			// if (strncmp(p, delim->delim_str, delim->delim_len) != 0)
			// 				break;		
			// 		}
			// 		else
			// 		{
			// 			printf(OL "Out of delimiters loop OK\n" RS);
			// 			break;
			// 		}		
			// 	}
				// ++delim;
			// 	printf("delimiters[++]: %s %d %d\n", delim->delim_str, delim->delim_len, delim->delim_type);
			// 	i++;
			// 	if (delim->delim_str == NULL && i < sizeof(delimiters) / sizeof(t_delim))
			// 		break;
			// }
		}
		else
		{
			while (!ft_isspace(*p))
			{
				// char *word = get_word(p);
				// int	len = get_wordlen(p);
				// printf("returned word %s\n", word);
				printf(LBLUE "ft_strlen(p): %zu\n" RS, ft_strlen(p));
				// printf(LBLUE "ft_strlen(word): %zu\n" RS, ft_strlen(word));
				add_token(&head, ft_substr(p, 0, get_wordlen(p)), TOK_WORD);
				printf("*p before p + wordlen: %c\n", *p);
				// break;
				// if (ft_strlen(p) - ft_strlen(word) >= 0)
				// {
				p = p + get_wordlen(p);
				printf("*p after p + wordlen: %c\n", *p);
				// 	printf("*p in word loop: %c\n", *p);
				// 	printf(OL "Out of word loop OK\n" RS);
					break ;
				// }
				// else
				// {
				// 	printf(OL "Out of word loop OK\n" RS);
			}
		}
        // else
        //     // make word
        // // make a token, add to list
		printf(NAVY "p before p++: %s\n" RS, p);
		if (p && *p != '\0')
		{
			p++;
			printf(NAVY "p after p++: %s\n" RS, p);
		}
		else
		{
			print_token(head);
			return (head);
		}
				
		// printf("p after p++: %s\n", p);
    }
	print_token(head);
    return(head);
}


        
        // printf("str p after check_delim: %s\n", p);

        // if (strncmp(p, "<<", 2) == 0)
        //     // make token type <<
        //     // add to the list
        //     // push p right after the token
        // else if (strncmp(p, ">>", 2) == 0)
        //     //
        // else if (*p == '>')
        // else if (*p == '|')
        //     // make pipe token
        // else if (*p == '|"')
        //     // 

				// else
		// {
		// 	word = p;
		// 	printf(LC "*word before loop: %c\n" RS, *word);
		// 	int	start = 0;
		// 	while (*word)
		// 	{
		// 		if (ft_isspace(*word) || *word == '>' || *word == '<' || *word == '|')
		// 			break;
		// 		printf(LC "*word inside loop: %c\n" RS, *word);
		// 		word++;
		// 	}
		// 	word++;
		// 	printf(LC "*word after loop: %c\n" RS, *word);
		// 	printf(LBLUE "ft_strlen(word): %zu\n" RS, ft_strlen(word));
		// 	add_token(&head, ft_substr(p, start, ft_strlen((word))), TOK_WORD);
		// 	if (ft_strlen(p) - ft_strlen(word) >= 0)
		// 	{
		// 		p = p + ft_strlen(word);
		// 		break;
		// 	}

		// }

      
