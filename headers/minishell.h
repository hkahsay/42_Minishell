#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include "../libft/libft.h"

# define WHITE      "\033[38;2;255;255;255m"
# define BLACK      "\033[38;2;0;0;0m"
# define R        "\033[38;2;255;0;0m"
# define LIME       "\033[38;2;0;255;0m"
# define BLUE       "\033[38;2;0;80;255m"
# define YELLOW     "\033[38;2;255;255;0m"
# define GCYAN      "\033[38;2;0;164;114m"
# define MAGENTA    "\033[38;2;255;0;255m"
# define SILVER     "\033[38;2;192;192;192m"
# define GRAY       "\033[38;2;128;128;128m"
# define MAR     "\033[38;2;128;0;0m"
# define OL      "\033[38;2;128;128;0m"
# define GREEN      "\033[38;2;0;128;0m"
# define PURPLE     "\033[38;2;128;0;128m"
# define TEAL       "\033[38;2;0;128;128m"
# define NAVY       "\033[38;2;0;0;128m"
# define DB         "\033[38;2;0;0;139m"
# define LC         "\033[38;2;224;255;255m"
# define MBLUE      "\033[38;2;58;62;92m"
# define LBLUE      "\033[38;2;114;121;179m"
# define GGREEN     "\033[38;2;14;195;6m"
# define OR	"\033[38;5;208m"

# define RS      "\033[0m"
# define clear() printf("\033[H\033[J");

//-------------------MY_ENV-----------------------

typedef struct s_envnode
{
	char *key;
	char *value;
	struct s_envnode *prev;
	struct s_envnode *next;
} t_envnode;

typedef struct s_prompt
{
	int			nbr_elm;
	char		*str;
}	t_prompt;

//-------------------LEXER------------------------

# define CLOSED 0
# define OPEN 1

// //assigning integer value to tokens = enumeration
typedef enum	e_toktype
{
	TOK_ERROR,
	TOK_WORD,
	TOK_D_QUOTE,
	TOK_S_QUOTE,
	TOK_REDIR_OUT,
	TOK_REDIR_IN,
	TOK_REDIR_OUT_APPEND,
	TOK_HEREDOC,
	TOK_PIPE,
	TOK_ERRQUOTE
	// TOK_UNKNOWN = 9
}	t_toktype;

typedef	struct s_delim
{
	char		*delim_str;
	int			delim_len;
	t_toktype	delim_type;
} t_delim;

typedef	struct s_quote
{
	char		*quote_str;
	int			quote_len;
	t_toktype	quote_type;
} t_quote;

// //define the delimiters as an array of t_toktype values
// t_delim delimiters[] = {
//     {">>", 2, TOK_REDIR_OUT_APPEND},
//     {"<<", 2, TOK_HEREDOC},
// 	{">", 1, TOK_REDIR_OUT},
//     {"<", 1, TOK_REDIR_IN},
//     {"|", 1, TOK_PIPE}
// };

    // {TOK_DQUOTE, "\"", 1},
	// {TOK_SQUOTE, "\'", 1},

typedef struct s_token
{
	char			*content;
	t_toktype		id;
	struct s_token	*next;
}	t_token;

//-------------------PARSER------------------------------

typedef struct s_redir_args
{
	int						type;
	char					*file;
	int						close_fd;
	struct s_redir_args		*next;
}  t_redir_args;

// typedef struct s_redir
// {
// 	int						type;
// 	char					*args;
// 	struct s_redir		*next;
// }  t_redir;


typedef struct s_cmd
{
	t_redir_args	*cmd_args;  // linked list of command arguments
	t_redir_args	*cmd_redir;  // linked list of redirections
	struct s_cmd	*next; // pointer to the next command in a pipeline
} t_cmd;

typedef struct	s_pipeline
{
	int					cmd_index;
	t_cmd				*cmd_node;
	struct s_pipeline	*next;
} t_pipeline;

typedef struct s_info
{
	// t_builtin_ptr	builtin[7];
	char			reserved_words[7]; //builtins
	char			**mini_envp;
	struct s_token	*envp_list;
	char			envp_flag;
	char			exit_flag;
	int				status;
	
}t_info;

// typedef struct s_stringln
// {
// 	char	*str;
// 	size_t	len;
// }	t_stringln;


/*MY_ENV*/
t_envnode	*dublicate_env(char **envp);
t_envnode	*create_my_envvar_node(char *key, char *value, int i);
void		free_myenvp(t_envnode *head);

void print_my_envp(t_envnode *temp);

/*PROMPT*/
void	prompt(char	*line); //t_envnode *my_envp, 

/*LEXER*/
t_token    *interp(char *input_str);
char    *skip_spaces(char *str);
char *check_delim(char **p, t_token **head);
int	is_delim_char(char c);
// t_token	*create_list_token(char  *epline); //, int id
// t_token *init_token_redirect(char *epline, int *i);
char *check_quotes(char **p, t_token **head);
int	is_quote(char c);
int eval_quote_type(char *q);
int	get_wordlen(char *p);

/*TOKEN*/
t_token	*init_token(t_token	*token);
t_token *new_token(char *content, t_toktype type);
void add_token(t_token **head, char *content, t_toktype type);
void print_token(t_token *temp);
// void	print_tokens(t_token *token_list);

/*PARSER*/
t_cmd	*parse(t_token *head);
// t_cmd	*tok_parser(char *input);
// t_parser	*init_parser(t_parser *parse);
// char	*new_parser(t_parser *parse, char *line);
// typedef int(*t_builtin_ptr)(t_llist *, t_info *);

//init minishell
//void	init_minishell();
/*EXECUTER*/
void execute(t_cmd *cmd);

#endif