#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
#include <termios.h>
#include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include "../libft/libft.h"
# include "structure.h"
# include "constants.h"

/*PROMPT*/
void		prompt(char	*line, t_envnode *mini_env);

/*----------------------signals-----------------*/
void 	sig_handlers(void);
void	sigint_handler(int	sig_num);
void	sig_quit_handler(int sig_num);
void	sig_do_nothing(int sig_num);
void	rl_replace_line(const char *text, int clear_undo);
void	ter_attr_handler(struct termios save);

/*INIT*/
t_envnode	*init_envnode(void);
t_token		*init_token(t_token	*token);
t_cmd		*init_cmd(void);
t_ppline	*init_ppline(void);

//void	init_minishell();

/*MINI_ENV*/
t_envnode	*duplicate_env(char **envp);
t_envnode	*create_mini_envvar_node(char *key, char *value, char *content);
void 		update_env_var(char *key, char *value);
void		ft_add_envlist(t_envnode *new_node, t_envnode **env);
int 		ft_setenv(char *name, char *value, char *content, t_envnode **env);
t_envnode	*find_env_var(char *key, t_envnode **current_dir);
void		ft_envnode_sort(t_envnode **mini_env);
t_envnode	*create_fuck(char *key);
t_envnode	*ft_join_env(t_envnode **mini_env);
// t_envnode	*create_mini_envvar_node(char *key, char *value);
// int			ft_setenv(char *name, char *value, t_envnode **env);
// t_envnode	*sort_envnode(t_envnode *lst);

int			ft_mini_env_size(t_envnode *mini_env_head);
char		**ft_mini_env_array(t_envnode *mini_env, int size);
char		*check_if_in_env(t_envnode *mini_env, char *arg);

int			find_env_key1(char *new_key, t_envnode *mini_env);
int			ft_mini_strncmp(const char *str1, const char *str2, size_t n);

//-----------sort--------
void		merge_sort_env(t_envnode **head_ref);
t_envnode*	sorted_merge_env(t_envnode* a, t_envnode* b);
void		front_back_split(t_envnode* source, t_envnode** front_ref, t_envnode** back_ref);

void		ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_strcmp(const char *s1, const char *s2);

/*LEXER*/
void		interp(char *line, t_envnode *mini_env);
char		*skip_spaces(char *str);
char		*check_delim(char **p, t_token **head);
int			is_delim_char(char c);
char		*check_quotes(char **p, t_token **head);
int			is_quote(char c);
int			eval_quote_type(char *q);
int			get_wordlen(char *p);
void		*expand_token_list(t_token **token_head, t_envnode *mini_env);
// t_token	*create_list_token(char  *epline); //, int id
// t_token *init_token_redirect(char *epline, int *i);

/*TOKEN*/
t_token		*new_token(char *content, t_toktype type);
t_token		*last_token(t_token *token_list);
void		add_token(t_token **head, char *content, t_toktype type);
char		*get_next_token(t_token *token, char *temp);
char		*expand_token(char **content, t_envnode *mini_env);
void		*merge_tokens(t_token **token_head);
void		*delete_tok_spaces(t_token **token_head);

/*UTILES*/
void		ft_strdel(char **as);
char		*ft_strjoin_free(char *s1, char *s2);
size_t		ft_strcspn(const char *str, const char *charset);
int			ft_strncmp2(char *s1, char *s2, int n);
int			ft_strset(const char *s1, char *s2);
// char		*strndup(const char *str, size_t n);
// char	*ft_strncpy(char *dest, const char *src, size_t n);

/*PARSER*/
void		*parse(t_token **token_head, t_envnode *mini_env);
void		*build_cmd_list(t_token **tok_cmd_list);

int			ft_token_list_size(t_token **tok_h);
int 		ft_count_pipes(t_token **tok_h);
// t_ppline		*create_array(t_cmd **cmd_head, int cmd_n);
int			ft_list_size(t_cmd *node);
void		ft_token_list_addback(t_token **head, t_token *new);

//-----------built_in-----------------
int			is_builtin(char **cmd, t_envnode *env_var);
int			ft_pwd(char **args, t_envnode **env_var);
int			ft_cd(char **args, t_envnode **env_var);
int			ft_echo(char **args, t_envnode **env_var);
int			ft_unset(char **args, t_envnode **env_var);
int			ft_export(char **cmd_args, t_envnode **mini_env);
int			ft_env(char **args, t_envnode **env_var);
int			ft_exit(char **args, t_envnode **env_var);
// typedef int(*t_builtin_ptr)(t_llist *, t_info *);
// int			mini_pwd2(t_envnode *env_list);

void		remove_from_list(t_envnode *mini_env, char *key);
int			delete_first_node(t_envnode **head, t_envnode *curr, char *key);

/*PRINT*/
void		print_token(t_token *temp);
void		print_token_list(t_token *token_list);
void		print_tok_cmd_list(t_token **tok_pp_list);

void		print_cmd_list(t_cmd *cmd_list);
void		print_ppline_list(t_ppline *ppline_list, int ppline_idx);
void 		print_mini_envp(t_envnode *temp);
void 		print_ex_envp(t_envnode *temp);
void		print_ex_sorted_envp(t_envnode *mini_env, char **cmd_arg);
void		printf_mini_env_array(char **mini_env_array);
// void		print_cmd(t_cmd *cmd);
// void		print_cmd_list1(t_token **cmd_list);
// void		print_array(char **array);
////----print_env_dif_level-----------
// void 		print_envp_nvalue(t_envnode *mini_env);
// void 		print_ex_no_value(t_envnode *mini_env);

/*EXECUTER*/
int			execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env);
t_ppline	*ft_new_ppline(void); //t_cmd **cmd_head, 
t_ppline	*build_ppline_array(t_cmd **cmd_head, int cmd_n, char	**mini_env_arr);
void		execute_cmd(t_ppline *ppline, char **mini_env_array, char **cmd_path);

int			search_path(t_ppline *ppline, char **mini_env_array, char **cmd_path);
char		*find_path(char **mini_env_array);

void		*ft_handle_word(t_ppline **new_ppline, t_token *cmd_word);
int			ft_count_args_cmd_word(t_token *ptr_cmd_word);
int			ft_handle_redir_all(t_ppline **new_ppline, t_token *ptr_cmd_red);
void		*ft_handle_heredoc(t_ppline **new_ppline, t_token **ptr_cmd_red);
void		*ft_handle_redir_in(t_ppline **new_ppline, t_token **ptr_cmd_red);
void		*ft_handle_redir_append(t_ppline **new_ppline, t_token **ptr_cmd_red);
void		*ft_handle_redir_out(t_ppline **new_ppline, t_token **ptr_cmd_red);

void		free_ppline(t_ppline **new_ppline, int *i);

// void		execute(t_token **tok_cmd, t_envnode *mini_env);
// void		execute1(t_pline *pline, t_envnode *mini_env);
// void	execute(t_pipeline *pipeline);

int			ft_bool_strcspn(const char *str, const char *charset);
void print_one_ppline(t_ppline *ppline);

/*ERROR*/
void		handle_input_error(t_token **token_head);
int			error_msg(const char *msg);
int			error_mem(void);
void		msg_error(char *error, int errnum);

/*FREE*/
void		free_mini_envp(t_envnode *head);
void		free_token_list(t_token *tokens);
void*		my_malloc(t_ppline *ppline, size_t size);
void		my_free_all(t_malloc **head);

#endif
