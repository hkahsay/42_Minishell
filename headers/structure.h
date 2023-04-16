#ifndef STRUCTURE_H
# define STRUCTURE_H

//-------------------MY_ENV-----------------------

typedef struct s_envnode
{
	char				*key;
	char				*value;
	char				*content;
	struct s_envnode	*prev;
	struct s_envnode	*next;
} t_envnode;

typedef struct s_prompt
{
	int		nbr_elm;
	char	*str;
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
	// struct s_token	*prev;

//-------------------PARSER------------------------------

typedef struct s_cmd
{
	// char 			*cmd_name;
	t_token			*cmd_word;  // linked list of command arguments
	t_token			*cmd_red;  // linked list of redirections
	struct s_cmd	*next; // pointer to the next command in a pipeline
} t_cmd;

typedef struct s_malloc
{
	void*	addr;
	struct	s_malloc* next;
} t_malloc;

//-------------------EXECUTER------------------------------

typedef int (*builtin_func)(char **, t_envnode **);

typedef struct s_builtin
{
    const char		*name;
    builtin_func	func;
} t_builtin;

// typedef struct	s_base
// {
// 	t_envnode		*mini_env;
// 	t_malloc		*malloc_head;

// }	t_base;

typedef struct	s_ppline
{
	char			*pp_first_cmd;
	char			*pp_first_cmd_path;
	char			**ppline_cmd;
	char			**ppline_env;
	int				ppline_idx;
	int				infile;
	int				outfile;
	int				heredoc;
	int				hdoc_fd[2];
	int				exit_status;
	t_malloc		*malloc_head;
	struct s_ppline	*next;
} t_ppline;

#endif
//-------------------INFO------------------------------

// typedef struct s_tok_io
// {
// 	t_envnode		*mini_envp;
// 	t_prompt		*prompt;
// 	t_token			*token;
// 	t_token			**tok_pp_li;
// 	t_cmd			*cmd;
// 	int				cmd_num;
	// t_builtin_ptr	builtin[7];
	// char			reserved_words[7]; //builtins
	// char			**mini_envp;
	// struct s_token	*envp_list;
	// char			envp_flag;
	// char			exit_flag;
	// int				status;

// }t_tok_io;

