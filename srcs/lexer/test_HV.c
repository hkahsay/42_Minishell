#include "../../headers/minishell.h"

// # define OPEN 1
// # define CLOSED 0

// static int ft_wordlen(char *input_str)
// {
//     int i = 0;

//     while (input_str[i] != '\0' && input_str[i] != ' ' && input_str[i] != '\t' && input_str[i] != '\n')
//         ++i;
//     return (i);
// }

// static char    *word_dupe(char *input_str)
// {
//     int i = 0;
//     int len = ft_wordlen(input_str);
//     char *word = malloc(sizeof(char) * (len + 1));

//     word[len] = '\0';
//     while (i < len)
//     {
//         word[i] = input_str[i];
//         ++i;
//     }
//     return (word);
// }

// static void    fill_words(char **array, char *input_str)
// {
//     int word_index = 0;

//     while (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')
//         ++input_str;
//     while (*input_str != '\0')
//     {
//         array[word_index] = word_dupe(input_str);
//         ++word_index;
//         while (*input_str != '\0' && *input_str != ' ' && *input_str != '\t' && *input_str != '\n')
//             ++input_str;
//         while (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')
//             ++input_str;
//     }
// }

// static int     count_words(char *input_str, char *q)
// {
//     int word_count = 0;
// 	int	word_quote_count = 0;
//     int quote_status = CLOSED;

//     while (*input_str == ' ' || *input_str == '\t' || *input_str == '\n')
// 		input_str++;
//     while (*input_str != '\0')
//     {
//         ++word_count;
//         while (*input_str != '\0' && *input_str != ' ' && *input_str != '\t' && *input_str != '\n')
//         {
// 			if ((ft_strncmp(input_str, q, ft_strlen(q)) == 0 && quote_status == CLOSED)) // && *(input_str + 1) != '\0'
//             {
//                 quote_status = OPEN;
// 				input_str++;
//                 while ((ft_strncmp(input_str, q, ft_strlen(q)) != 0))
//                     input_str++;
//             }
//             if ((ft_strncmp(input_str, q, ft_strlen(q)) == 0 && quote_status == OPEN))
//             {
//                 quote_status = CLOSED;
//                 word_quote_count++;
//                 input_str++;
//                 break ;
//             }
// 			else
// 				input_str++;
// 		}
//         if (quote_status == OPEN && (*input_str == ' ' || *input_str == '\t' || *input_str == '\n'))
//         {
//             while ((*input_str == ' ' || *input_str == '\t' || *input_str == '\n'))
//                 input_str++;
//             if ((ft_strncmp(input_str, q, ft_strlen(q)) == 0 && quote_status == OPEN))
//             {
//                 quote_status = CLOSED;
//                 word_quote_count++;
//                 input_str++;
//                 break ;
//             }
//             input_str++;
//         }
//         while (*input_str != '\0' && *input_str != ' ' && *input_str != '\t' && *input_str != '\n')
//         {
//             input_str++;
//         }
//         while ((*input_str == ' ' || *input_str == '\t' || *input_str == '\n'))
//             input_str++;
// 	}
// 	if (quote_status == OPEN && *input_str == '\0')
//     {
//         printf("error");
//         return (-1);
//     }
//     return (word_count);
// }

// char    **ft_split_line(char *input_str)
// {
//     int     word_count;
//     char    **array;
// 	char *quote = "\"";

//     word_count = count_words(input_str, quote);
//     array = malloc(sizeof(char *) * (word_count + 1));

//     array[word_count] = 0;
//     fill_words(array, input_str);
//     int i = 0;
//     while (array[i])
//     {
//         printf("%s\n", array[i++]);
//     }
//     return (array);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPEN 1
#define CLOSED 0

static int ft_wordlen(char *input_str, char *delimiters)
{
    int i = 0;

    while (input_str[i] != '\0' && !strchr(delimiters, input_str[i]))
        ++i;
    return (i);
}

static char *word_dupe(char *input_str, char *delimiters)
{
    int i = 0;
    int len = ft_wordlen(input_str, delimiters);
    char *word = malloc(sizeof(char) * (len + 1));

    word[len] = '\0';
    while (i < len)
    {
        word[i] = input_str[i];
        ++i;
    }
    return (word);
}

static t_token *new_token(char *value, t_toktype type)
{
    t_token *token = malloc(sizeof(t_token));
    token->value = value;
    token->type = type;
    token->next = NULL;
    return (token);
}

static void add_token(t_token **head, char *value, t_toktype type)
{
    t_token *token = new_token(value, type);

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

static void fill_words(t_token **head, char *input_str, char *delimiters)
{
    while (*input_str != '\0')
    {
        while (*input_str != '\0' && strchr(delimiters, *input_str))
            ++input_str;
        if (*input_str != '\0')
        {
            add_token(head, word_dupe(input_str, delimiters), TOK_WORD);
            input_str += ft_wordlen(input_str, delimiters);
        }
    }
}

void print_tokens(t_token *token_list)
{
    t_token *current = token_list;

    while (current != NULL)
    {
        printf("Type: %d, Token: %s\n", current->type, current->token);
        current = current->next;
    }
}

t_token *ft_split_line(char *input_str, char *delimiters)
{
    t_token *head = NULL;
    t_token *print;

    print = head;

    fill_words(&head, input_str, delimiters);
    print_tokens(print);
    return (head);
}

// In your case, you can define the delimiters using the #define statements you've provided. You can modify the fill_words function to take in an array of t_toktype values instead of a string array for the delimiters. Here's an example of how you can modify the fill_words function:

// c
// Copy code
// static void fill_words(t_token **head, char *input_str, t_toktype *delimiters)
// {
//     int word_index = 0;

//     while (*input_str != '\0')
//     {
//         while (*input_str != '\0' && is_delimiter(*input_str, delimiters))
//             ++input_str;
//         if (*input_str != '\0')
//         {
//             char *word = word_dupe(input_str, delimiters);
//             t_token *new_token = create_token(word, get_token_type(word, delimiters));
//             add_token(head, new_token);
//             input_str += ft_wordlen(input_str, delimiters);
//         }
//     }
// }
// Here, the is_delimiter function is used to check if the current character is a delimiter or not. You can define it as follows:

// c
// Copy code
// static int is_delimiter(char c, t_toktype *delimiters)
// {
//     while (*delimiters != 0)
//     {
//         if (get_token_type(&c, delimiters) != TOK_ERROR)
//             return 1;
//         delimiters++;
//     }
//     return 0;
// }
// You can then define the delimiters as an array of t_toktype values like this:

// c
// Copy code
// t_toktype delimiters[] = {
//     TOK_REDIR_OUT,
//     TOK_REDIR_IN,
//     TOK_REDIR_APPEND,
//     TOK_HEREDOC,
//     TOK_PIPE,
//     0
// };
// And call the ft_split_line function like this:

// c
// Copy code
// t_token *head = NULL;
// ft_split_line(line, delimiters, &head);
// print_token_list(head);
// This should print out the list of tokens to the console.