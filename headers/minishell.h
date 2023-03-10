
#ifndef MINISHELL_H
# define MINISHELL_H

# define clear() printf("\033[H\033[J");

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

// typedef int(*t_builtin_ptr)(t_llist *, t_info *);

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

typedef struct s_list
{
	void			*key;
	void			*value;
	struct s_list	*prev;
	struct s_list	*next;
}t_list;

typedef struct s_envnode
{
	char *key;
	char *value;
	struct s_envnode *prev;
	struct s_envnode *next;
} t_envnode;

/*my environment*/
t_envnode *dublicate_env(char **envp);
t_envnode *create_my_envvar_node(char *key, char *value, int i);

//init minishell
//void	init_minishell();

#endif