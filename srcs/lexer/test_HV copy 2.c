#include "../../headers/minishell.h"

# define OPEN 1
# define CLOSED 0

static int ft_wordlen(char *input_str)
{
    int i = 0;

    while (input_str[i] != '\0' && input_str[i] != ' ' && input_str[i] != '\t' && input_str[i] != '\n')
        ++i;
    return (i);
}

static char    *word_dupe(char *input_str)
{
    int i = 0;
    int len = ft_wordlen(input_str);
    char *word = malloc(sizeof(char) * (len + 1));

    printf(PURPLE "\n len: %d\n" RS,  len);
    word[len] = '\0';
    while (i < len)
    {
        word[i] = input_str[i];
        ++i;
    }
    return (word);
}

static void    fill_words(char **array, char *input_str)
{
    int word_index = 0;

    while (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')
        ++input_str;
    while (*input_str != '\0')
    {
        array[word_index] = word_dupe(input_str);
        ++word_index;
        while (*input_str != '\0' && *input_str != ' ' && *input_str != '\t' && *input_str != '\n')
            ++input_str;
        while (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')
            ++input_str;
    }
}

// static int if_delimiter(char c, char delimiter)
// {

//     if (ft_strncmp(input_str, q, ft_strlen(q)) == 0)
//         return (1);
//     return (0);    
// }

static int     count_words(char *input_str, char *q)
{
    int word_count = 0;
	int	word_quote_count = 0;
    int quote_status = CLOSED;

    while (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')
		input_str++;
    while (*input_str != '\0')
    {
        if (quote_status == CLOSED)
            ++word_count;
        printf("\nnum_words: %d\n", word_count);
		printf("\n1:quote_status: %d *str: %c\n", quote_status, *input_str);    
        while (*input_str != '\0' && *input_str != ' ' && *input_str != '\t' && *input_str != '\n')
        {
            printf("*input_str in while loop 1: %c\n", *input_str);
			if ((ft_strncmp(input_str, q, ft_strlen(q)) == 0 && quote_status == CLOSED)) // && *(input_str + 1) != '\0'
            {
                quote_status = OPEN;
				input_str++;
                printf("\n2:found open quote: %d *str: %c\n", quote_status, *input_str);
                // if ((*input_str != '\0' && *input_str != ' ' && *input_str != '\t' && *input_str != '\n') && (ft_strncmp(input_str, q, ft_strlen(q)) != 0))
                // {
                //      input_str++;
                //      printf("0 left here\n"); 
                // }
                   
                printf(LIME "1 left here\n" RS);    
            }
            if ((*input_str != '\0'  && quote_status == OPEN && (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')))
                break;
            printf("ft_strncmp: %d *input_str %c, ft_strlen(q) %zu\n", ft_strncmp(input_str, q, ft_strlen(q)), *input_str, ft_strlen(q)); 
            if ((ft_strncmp(input_str, q, ft_strlen(q)) == 0 && quote_status == OPEN))
            {
                quote_status = CLOSED;
                word_quote_count++;
                input_str++;
                printf(BLUE "2 left here\n" RS); 
                break ;
            }
			else
				input_str++;
		}
        // if (quote_status == OPEN && (*input_str == ' ' || *input_str == '\t' || *input_str == '\n'))
        // {
        //     while ((*input_str == ' ' || *input_str == '\t' || *input_str == '\n'))
        //         input_str++;
        //     if ((ft_strncmp(input_str, q, ft_strlen(q)) == 0 && quote_status == OPEN))
        //     {
        //         quote_status = CLOSED;
        //         word_quote_count++;
        //         input_str++;
        //         break ;
        //     }
        //     input_str++;
        // }
        // while (*input_str != '\0' && *input_str != ' ' && *input_str != '\t' && *input_str != '\n')
        // {
        //     input_str++;
        // }
        while ((*input_str != '\0' && (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')))
        {
            // if (quote_status == OPEN) //(ft_strncmp(input_str, q, ft_strlen(q)) != 0 &&  // && (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')
            //    input_str++;
            // if ((ft_strncmp(input_str, q, ft_strlen(q)) == 0 && quote_status == OPEN))
            // {
            //     quote_status = CLOSED;
            //     // word_quote_count++;
            //     input_str++;
            //     break ;
            // }
            // else
                // input_str++;
            // if ((ft_strncmp(input_str, q, ft_strlen(q)) == 0 && quote_status == CLOSED)) // && *(input_str + 1) != '\0'
            // {
            //     quote_status = OPEN;
			// 	input_str++;
            //     while ((ft_strncmp(input_str, q, ft_strlen(q)) != 0))
            //         input_str++;
            // }
            if (quote_status == OPEN) //(ft_strncmp(input_str, q, ft_strlen(q)) == 0 && 
            {
                printf("\n7:found open quote: %d *str: %c\n", quote_status, *input_str);
                while ((*input_str != '\0' && (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')))
                    input_str++;
                // quote_status = CLOSED;
                // word_quote_count++;
                // input_str++;
                // break ;
            }
			else
				input_str++;
            printf(R "I was here\n" RS);
        }
        // input_str++;
	}
	if (quote_status == OPEN && *input_str == '\0')
    {
        printf("error");
        return (-1);
    }
    return (word_count);
}

char    **split_line(char *input_str)
{
    int     word_count;
    char    **array;
	char *quote = TOK_DQUOTE;


    word_count = count_words(input_str, quote);
    if (!word_count)
        return (NULL);
    printf(PURPLE "\n word_count: %d\n" RS,  word_count);
    array = malloc(sizeof(char *) * (word_count + 1));
    if (!array)
        return (NULL);
    array[word_count] = 0;
    fill_words(array, input_str);
    int i = 0;
    while (array[i])
    {
        printf("%s\n", array[i++]);
    }
    return (array);
}

// void print_tokens(t_token *token_list)
// {
//     t_token *current = token_list;

//     while (current != NULL)
//     {
//         printf("Type: %d, Token: %s\n", current->type, current->content);
//         current = current->next;
//     }
// }

// # define TOK_WORD
// # define TOK_DQUOTE "\""
// # define TOK_SQUOTE "\'"
// # define TOK_REDIR_OUT ">"
// # define TOK_REDIR_IN "<"
// # define TOK_REDIR_OUT_APPEND ">>"
// # define TOK_HEREDOC "<<"
// # define TOK_PIPE "|"
// // # define EXP_FIELD
// // # define FIELD

// #define Q_OPEN 1
// #define Q_CLOSED 0


// //assigning integer value to tokens = enumeration
// typedef enum	e_toktype
// {
// 	TOK_ERROR = 0,
// 	TOK_WORD = 1,
// 	TOK_DQUOTE = 2,
// 	TOK_SQUOTE = 3,
// 	TOK_REDIR_OUT = 4,
// 	TOK_REDIR_IN = 5,
// 	TOK_REDIR_OUT_APPEND = 6,
// 	TOK_HEREDOC = 7,
// 	TOK_PIPE = 8
// }	t_toktype;


// //define the delimiters as an array of t_toktype values
// t_toktype delimiters[] = {
//     TOK_DQUOTE,
// 	TOK_SQUOTE,
//     TOK_REDIR_OUT,
//     TOK_REDIR_IN,
//     TOK_REDIR_OUT_APPEND,
//     TOK_HEREDOC,
//     TOK_PIPE
// };


// typedef struct s_token
// {
//     char	*content;
//     t_toktype type;
//     struct s_token *next;
// } t_token;

// static int ft_wordlen(char *input_str, t_toktype *delimiters)
// {
//     int i = 0;

//     while (input_str[i] != '\0' && !is_delimiter(input_str[i], delimiters))
//         ++i;
//     return (i);
// }

// static char *word_dupe(char *input_str, char *delimiters)
// {
//     int i = 0;
//     int len = ft_wordlen(input_str, delimiters);
//     char *word = malloc(sizeof(char) * (len + 1));

//     word[len] = '\0';
//     while (i < len)
//     {
//         word[i] = input_str[i];
//         ++i;
//     }
//     return (word);
// }

// static t_token *new_token(char *content, t_toktype type)
// {
//     t_token *token = malloc(sizeof(t_token));
//     token->content = content;
//     token->type = type;
//     token->next = NULL;
//     return (token);
// }

// static void add_token(t_token **head, char *value, t_toktype type)
// {
//     t_token *token = new_token(value, type);

//     if (*head == NULL)
//     {
//         *head = token;
//     }
//     else
//     {
//         t_token *current = *head;
//         while (current->next != NULL)
//         {
//             current = current->next;
//         }
//         current->next = token;
//     }
// }

// // is_delimiter function is used to check if the current character is a delimiter or not 

// static int is_delimiter(char c, t_toktype *delimiters)
// {
//     while (*delimiters != 0)
//     {
//         if (c = get_token_type(delimiters))
//             return 1;
//         delimiters++;
//     }
//     return 0;
// }

// static t_toktype get_token_type(char *str, t_toktype *delimiters)
// {
//     if (*str == '\0')
//         return (TOK_ERROR);

//     while (*delimiters != 0)
//     {
//         if (strncmp(str, *delimiters, strlen(*delimiters)) == 0)
//             return (*delimiters);
//         ++delimiters;
//     }
//     return (TOK_WORD);
// }

// /*The fill_words function first loops through the input string and checks for delimiters. 
// If the current character is a delimiter, it skips to the next character. 
// If the current character is not a delimiter, it creates a new token using the word_dupe 
// function to extract the word and the get_token_type function to determine the token type. 
// The add_token function is then called to add the new token to the linked list. 
// Finally, the function updates the input string pointer to the next word by adding the length 
// of the current word and the delimiters.*/
// static void fill_words(t_token **head, char *input_str, t_toktype *delimiters)
// {
//     int word_index;
//     char *word;
//     t_token *new_token;

//     word_index = 0;
//     new_token = NULL;
//     while (*input_str != '\0')
//     {
//         while (*input_str != '\0' && is_delimiter(*input_str, delimiters))
//             ++input_str;
//         if (*input_str != '\0')
//         {
//             word = word_dupe(input_str, delimiters);
//             new_token = create_token(word, get_token_type(word, delimiters));
//             add_token(head, new_token->content, new_token->type);
//             input_str += ft_wordlen(input_str, delimiters);
//         }    
//     }
// }

// t_token *ft_split_line(t_token *head, char *input_str, t_toktype *delimiters)
// {
//     // t_token *print;

//     // print = head;
//     fill_words(&head, input_str, delimiters);
//     // print_tokens(print);
//     return (head);
// }

// // In your case, you can define the delimiters using the #define statements you've provided. 
// //You can modify the fill_words function to take in an array of t_toktype values instead of 
// //a string array for the delimiters. Here's an example of how you can modify the fill_words function:

// // c
// // Copy code
// // static void fill_words(t_token **head, char *input_str, t_toktype *delimiters)
// // {
// //     int word_index = 0;

// //     while (*input_str != '\0')
// //     {
// //         while (*input_str != '\0' && is_delimiter(*input_str, delimiters))
// //             ++input_str;
// //         if (*input_str != '\0')
// //         {
// //             char *word = word_dupe(input_str, delimiters);
// //             t_token *new_token = create_token(word, get_token_type(word, delimiters));
// //             add_token(head, new_token);
// //             input_str += ft_wordlen(input_str, delimiters);
// //         }
// //     }
// // }
// // Here, the is_delimiter function is used to check if the current character is a delimiter or not. You can define it as follows:

// // c
// // Copy code
// // static int is_delimiter(char c, t_toktype *delimiters)
// // {
// //     while (*delimiters != 0)
// //     {
// //         if (get_token_type(&c, delimiters) != TOK_ERROR)
// //             return 1;
// //         delimiters++;
// //     }
// //     return 0;
// // }
// // You can then define the delimiters as an array of t_toktype values like this:

// // c
// // Copy code
// // t_toktype delimiters[] = {
// //     TOK_REDIR_OUT,
// //     TOK_REDIR_IN,
// //     TOK_REDIR_APPEND,
// //     TOK_HEREDOC,
// //     TOK_PIPE,
// //     0
// // };
// // And call the ft_split_line function like this:

// // c
// // Copy code
// // t_token *head = NULL;
// // ft_split_line(line, delimiters, &head);
// // print_token_list(head);
// // This should print out the list of tokens to the console.