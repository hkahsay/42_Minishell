#ifndef MINISHELL_H
# define MINISHELL_H

# define clear() printf("\033[H\033[J");

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

# define WORD 1
# define REDIR_OUT_STR ">"
# define REDIR_IN_STR "<"
# define REDIR_OUT_APPEND_STR ">>"
# define HEREDOC_STR "<<"
# define PIPE_STR "|"
# define EXP_FIELD 7
# define FIELD 8

//tokens
typedef enum	e_toktype
{
	TOK_ERROR,
	TOK_WORD,
	QUOTE,
	TOK_REDIR_OUT,
	TOK_REDIR_IN,
	TOK_REDIR_APPEND,
	TOK_HEREDOC,
	TOK_PIPE
}	t_toktype;

char *delimiters[] = {
    " ",
    TOK_REDIR_OUT_STR,
    TOK_REDIR_IN_STR,
    TOK_REDIR_APPEND_STR,
    TOK_HEREDOC_STR,
    TOK_PIPE_STR,
    NULL
};

typedef struct s_token
{
    char *value;
    t_toktype type;
    struct s_token *next;
} t_token;


typedef struct s_stringln
{
	char	*str;
	size_t	len;
}	t_stringln;

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

typedef struct s_list
{
	char			*content;
	int				id_token;
	struct s_list	*next;

}	t_list;

typedef struct s_info
{
	// t_builtin_ptr	builtin[7];
	char			reserved_words[7]; //builtins
	char			**mini_envp;
	struct s_list	*envp_list;
	char			envp_flag;
	char			exit_flag;
	int				status;
	
}t_info;

// typedef struct s_list
// {
// 	void			*key;
// 	void			*value;
// 	struct s_list	*prev;
// 	struct s_list	*next;
// }t_list;

/*copy into my environment*/
t_envnode	*dublicate_env(char **envp);
t_envnode	*create_my_envvar_node(char *key, char *value, int i);
void		free_myenvp(t_envnode *head);

void print_my_envp(t_envnode *temp);

void	prompt(char	*line); //t_envnode *my_envp, 
t_stringln	*ft_strdup_stringln(const char *str);

t_token    **ft_split_line(char *str);

t_list	*create_list_token(char  *epline); //, int id
t_list *init_token_redirect(char *epline, int *i);
t_list	*init_token(t_list	*token);

char	*epur_str(char *str);
char	**split_line(char const *s, char c);

// t_list	*init_token(char *line);
int	classification(t_list *token, char *line);
// int		ft_strlen(char *str);
// void	ft_putstr_fd(char *str, int fd);
// char	*classification(t_list *token, char *content, int id);
// char	*word_token(char *word);
// int		is_word(const char *str);
// int	is_space(char c);
// char	**ft_split(const char *s, char c);
// int	ft_strlen(const char *str);
// char	*ft_substr(char const *s, unsigned int start, size_t len);

// typedef int(*t_builtin_ptr)(t_llist *, t_info *);

//init minishell
//void	init_minishell();

#endif