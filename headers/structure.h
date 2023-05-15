#ifndef STRUCTURE_H
# define STRUCTURE_H

int	g_exit_status;
//-------------------MY_ENV-----------------------

typedef struct s_envnode
{
	char				*key;
	char				*value;
	char				*content;
	struct s_envnode	*prev;
	struct s_envnode	*next;
}	t_envnode;

typedef struct s_prompt
{
	int		nbr_elm;
	char	*str;
}	t_prompt;

//-------------------LEXER------------------------

# define CLOSED 0
# define OPEN 1

// assigning integer value to tokens = enumeration
typedef enum e_toktype
{
	T_ERR,
	T_W,
	T_DQ,
	T_SQ,
	T_RO,
	T_RI,
	T_ROA,
	T_RHD,
	T_PP,
	T_SP,
	T_ERQ,
	T_EMPTY,
	TOK_NONE
}	t_toktype;

typedef struct s_lim
{
	char		*lim_str;
	int			lim_len;
	t_toktype	lim_type;
}	t_lim;

typedef struct s_quote
{
	char		*quote_str;
	int			q_len;
	t_toktype	quote_type;
}	t_quote;

typedef struct s_token
{
	char			*content;
	t_toktype		id;
	struct s_token	*next;
}	t_token;
//-------------------PARSER------------------------------

typedef struct s_cmd
{
	t_token			*cmd_word;
	t_token			*cmd_red;
	struct s_cmd	*next;
}	t_cmd;

//-------------------EXECUTER------------------------------

typedef struct s_ppl	t_ppl;
typedef int				(*builtin_func)(t_ppl **);

typedef struct s_builtin
{
	const char		*name;
	builtin_func	func;
}	t_builtin;

typedef struct s_ppl
{
	char			*pp_first_cmd;
	char			**ppl_cmd;
	char			**pp_arr_env;
	int				ppl_idx;
	int				pp_pid;
	int				saved_stdin;
	int				saved_stdout;
	int				pp_builtin_status;
	int				pp_red_status;
	int				pp_infile;
	int				pp_outfile;
	int				pp_heredoc_status;
	char			*pp_heredoc_eof;
	int				pp_fd_in;
	int				pp_fd_out;
	int				pp_append_fd;
	int				pp_exit;
	t_envnode		*pp_list_env;
	t_builtin		*builtin;
	t_cmd			*cmd;
	struct s_ppl	*next;
	struct s_ppl	*first;
}	t_ppl;
#endif
