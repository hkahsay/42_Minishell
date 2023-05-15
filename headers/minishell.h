#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include "../libft/libft.h"
# include "structure.h"
# include "constants.h"

/*----------------------prompt-----------------*/
void		prompt(char	*line, t_envnode *mini_env);
/*----------------------signals-----------------*/
void		sig_handlers(void);
void		sigint_handler(int sig_num);
void		sig_quit_handler(int sig_num);
void		sig_do_nothing(int sig_num);
void		rl_replace_line(const char *text, int clear_undo);
void		ter_attr_handler_on(void);
void		ter_attr_handler_off(void);
void		signal_handler2(int sig);
void		signals_default(void);
void		signal_at_beginning(void);
void		handle_signal(struct termios *saved);
/*----------------------init-----------------*/
t_envnode	*init_envnode(void);
t_token		*init_token(t_token	*token);
t_cmd		*init_cmd(void);
t_ppl		*init_ppl(void);
/*----------------------mini_env-----------------*/
t_envnode	*duplicate_env(char **envp);
t_envnode	*create_mini_envvar_node(char *key, char *value, char *content);
void		update_env_var(char *key, char *value);
void		ft_add_envlist(t_envnode *new_node, t_envnode **env);
int			ft_setenv(char *name, char *value, char *content, t_envnode **env);
t_envnode	*find_env_var(char *key, t_envnode **current_dir);
char		*find_env_var2(char *key, t_envnode **current_dir);
void		ft_envnode_sort(t_envnode **mini_env);
int			home_not_set(char *home, char *pwd);
t_envnode	*create_fuck(char *key);
t_envnode	*ft_join_env(t_envnode **mini_env);

int			mini_env_size(t_envnode *mini_env_head);
char		**mini_env_arr(t_envnode *mini_env, int size);
char		*check_if_in_env(t_envnode *mini_env, char *arg);
char		*get_env_key(char *env_var);
char		*get_env_value(char *env_var);

int			find_env_key1(char *new_key, t_envnode *mini_env);
int			ft_mini_strncmp(const char *str1, const char *str2, size_t n);
/*----------------------sort-----------------*/
void		merge_sort_env(t_envnode **head_ref);
t_envnode	*sorted_merge_env(t_envnode *a, t_envnode *b);
void		front_back_split(t_envnode *source, t_envnode \
**front_ref, t_envnode **back_ref);

void		ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_strcmp(const char *s1, const char *s2);
/*----------------------lexer-----------------*/
void		interp(char *line, t_envnode *mini_env);
char		*skip_spaces(char *str);
char		*check_lim(char **p, t_token **head);
int			is_lim_char(char c);
char		*check_quotes(char **p, t_token **head);
int			is_q(char c);
int			eqt(char *q);
int			get_wordlen(char *p);
void		*exp_toklist(t_token **token_head, t_envnode *mini_env);
/*----------------------token-----------------*/
t_token		*new_token(char *content, t_toktype type);
t_token		*last_token(t_token *token_list);
void		add_token(t_token **head, char *content, t_toktype type);
char		*get_next_token(t_token *token, char *temp);
char		*exp_tok(char **cont, t_envnode *mini_env);
void		*merge_tokens(t_token **token_head);
void		*delete_tok_spaces(t_token **token_head);
void		ft_export_args(char *cmd, t_envnode **env_lst);
/*----------------------utils-----------------*/
void		ft_strdel(char **as);
char		*ft_strjoin_free(char *s1, char *s2);
size_t		ft_strcspn(const char *str, const char *charset);
int			ft_strncmp2(char *s1, char *s2, int n);
/*----------------------parser-----------------*/
void		*parse(t_token **token_head, t_envnode *mini_env);
void		*build_cmd_list(t_token **tok_cmd_list);

int			ft_token_list_size(t_token **tok_h);
int			ft_count_pipes(t_token **tok_h);
int			ft_list_size(t_cmd *node);
void		ft_token_list_addback(t_token **head, t_token *new);
/*----------------------builtin-----------------*/
int			check_if_builtin(char *first_cmd);
int			execute_builtin(t_ppl **ppl);
int			ft_pwd(t_ppl **ppl);
int			ft_cd(t_ppl **ppl);
int			ft_echo(t_ppl **ppl);
int			ft_unset(t_ppl **ppl);
int			ft_export(t_ppl **ppl);
int			ft_env(t_ppl **ppl);
int			ft_exit(t_ppl **ppl);
int			get_dir(char *arg, char *home, t_ppl **ppl);
t_envnode	*export_no_cmd(t_envnode **mini_env);
int			find_flag(char *cmd);
int			print_and_return(t_ppl **ppl, int flag_echo, int flag_n);
int			ft_error_print(char **arg);
int		remove_from_list(t_envnode **mini_env, char *key);
int			delete_first_node(t_envnode ***hd, char *key);
/*----------------------execute-----------------*/
t_ppl		*ft_new_ppl(void); //t_cmd **cmd_head,
t_ppl		*build_ppl(t_cmd **cmd_head, int cmd_n, t_envnode *mini_env);
void		*init_pipe(t_ppl **ppl, int ppl_idx);
void		execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env);
int			execute_single_builtin(t_ppl *ppl);
int			execute_pipe_cmd(t_ppl *ppl);
void		execute_parent(t_ppl **ppl);
int			execute_kid(t_ppl *ppl);
int			execute_fork_cmd(t_ppl *ppl);
int			execute_to_builtin(t_ppl *ppl);
int			execute_heredoc(t_ppl **ppl);
void		wait_execution(t_ppl **ppl);
void		finish_exec(t_ppl **ppl);
void		finish_multi_exec(t_ppl **p_ppl);
/*----------------------path-----------------*/
int			search_path(t_ppl *ppl, char **cmd_path);
int			find_curr_dir(char **path);
char		*find_path(char **mini_env_array);
/*----------------------cmd-----------------*/
void		*handle_word(t_ppl **new_ppl, t_token *cmd_word);
int			count_args_cmd_word(t_token *ptr_cmd_word);
int			ft_handle_red_all(t_ppl **new_ppl, t_token *ptr_cmd_red);
int			ft_handle_heredoc(t_ppl **new_ppl, t_token **ptr_cmd_red);
int			ft_handle_redir_in(t_ppl **new_ppl, \
t_token **ptr_cmd_red);
int			ft_handle_redir_append(t_ppl **new_ppl, \
t_token **ptr_cmd_red);
int			ft_handle_redir_out(t_ppl **new_ppl, t_token **ptr_cmd_red);
/*----------------------fds-----------------*/
void		dup_fds(t_ppl **ppl);
void		dup_red_fds(t_ppl **ppl);
void		dup_saved_stds(t_ppl **ppl);
void		dup2_saved_stds(t_ppl **ppl);
void		*manage_dup(t_ppl **ppl_p);
void		close_red_fds(t_ppl **ppl);
void		close_fds(t_ppl **ppl);
void		close_all_fds(t_ppl **ppl);
void		close_saved_stds(t_ppl **ppl);
void		close_fd(t_ppl **ppl);
void		close_all_fds(t_ppl **ppl);
void		close_fds(t_ppl **ppl);
void		close_red_fds(t_ppl **ppl);
void		wait_status(t_ppl *ppl);
/*----------------------error-----------------*/
int			handle_input_error(t_token **token_head);
int			input_error_01(t_token **tok_head);
int			input_error_02(t_token **tok_head);
int			handle_input_pipe(void);
int			handle_input_2pipes(void);
int			handle_input_red_error(void);
int			handle_input_red_pipe(char **content);
void		msg_error(char *error, int errnum);
/*----------------------free-----------------*/
void		free_mini_envp(t_envnode *head);
void		free_token_list(t_token *tokens);
void		free_ppl(t_ppl **new_ppl, int *i);
void		free_one_ppl(t_ppl **new_ppl);
/*----------------------print-----------------*/
void		print_token(t_token *temp);
void		print_token_list(t_token *token_list);
void		print_tok_cmd_list(t_token **tok_pp_list);
void		print_cmd_list(t_cmd *cmd_list);
void		print_mini_envp(t_envnode *temp);
void		print_ex_envp(t_envnode *temp);
void		print_ex_sorted_envp(t_envnode *mini_env);
void		print_mini_env_array(char **mini_env_array);
void		print_all_pipeline(t_ppl *line);
void		print_one_ppl(t_ppl *ppl);
void		print_ppl_list(t_ppl *ppl_list, int ppl_idx);

#endif
