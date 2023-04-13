#ifndef STRUCTURE_H
# define STRUCTURE_H

//-------------------MY_ENV-----------------------

typedef struct s_envnode
{
	char *key;
	char *value;
	char *content;
	struct s_envnode *prev;
	struct s_envnode *next;
} t_envnode;

typedef struct s_prompt
{
	int			nbr_elm;
	char		*str;
	// t_envnode	*m_env;
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
	TOK_SPACE,
	TOK_ERRQUOTE,
	TOK_EMPTY,
	TOK_NONE
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

typedef struct s_token
{
	char			*content;
	t_toktype		id;
	struct s_token	*next;
}	t_token;

//-------------------PARSER------------------------------

typedef struct s_cmd
{
	// char 			*cmd_name;
	t_token		*cmd_word;  // linked list of command arguments
	t_token		*cmd_red;  // linked list of redirections
	struct s_cmd	*next; // pointer to the next command in a pipeline
} t_cmd;

//-------------------EXECUTER------------------------------

typedef struct	s_pmd
{
	char			*cmd;
	char			**pmd_cmd;
	int				pmd_index;
	int				infile;
	// int				outfile;
	int				heredoc;
	int				hdoc_fd[2];
	struct s_pmd	*next;
} t_pmd;

typedef int (*builtin_func)(char **, t_envnode **);

typedef struct s_builtin
{
    const char *name;
    builtin_func func;
} t_builtin;

//-------------------INFO------------------------------

typedef struct s_tok_io
{
	t_envnode		*mini_envp;
	t_prompt		*prompt;
	t_token			*token;
	t_token			**tok_pp_li;
	t_cmd			*cmd;
	int				cmd_num;
	// t_builtin_ptr	builtin[7];
	// char			reserved_words[7]; //builtins
	// char			**mini_envp;
	// struct s_token	*envp_list;
	// char			envp_flag;
	// char			exit_flag;
	// int				status;

}t_tok_io;

#endif


// //-------------------MY_ENV-----------------------

// typedef struct s_envnode
// {
// 	char *key;
// 	char *value;
// 	struct s_envnode *prev;
// 	struct s_envnode *next;
// } t_envnode;

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


// typedef struct s_redir
// {
// 	int						type;
// 	char					*args;
// 	struct s_redir		*next;
// }  t_redir;

// typedef struct s_wr_node
// {
// 	int					type;
// 	char				*file;
// 	int					close_fd;
// 	struct s_wr_node	*next;
// }  t_wr_node;

// //---------------built-in----------------
// # define PWD 1
// # define CD 2
// # define CMD_ECHO 3
// # define UNSET 4
// # define EXPORT 5
// # define ENV 6
// # define EXIT 7

// typedef struct s_stringln
// {
// 	char	*str;
// 	size_t	len;
// }	t_stringln;