/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkahsay <hkahsay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:15:44 by hkahsay           #+#    #+#             */
/*   Updated: 2023/02/27 15:00:19 by hkahsay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 1
# define SPACE 2
# define SINGLE_QUOTE 3
# define DOUBLE_QUOTE 4
# define REDIR_OUT 5
# define REDIR_IN 6
# define REDIR_APPEND 7
# define HERE_DOC 8
# define PIPE 9

typedef struct s_list
{
	int				id_token;
	// int				id_word;
	void			*class;
	struct s_list	*next;
	char			*str;
	char			field;
	char			exp_field;
	struct s_cmd	*cmd;
}	t_list;

typedef struct s_cmd
{
	pid_t				process_id;
	char				*content;
	int					redir_out;
	int					redir_in;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_prompt
{
	int			nbr_elm;
	char		*str;
}	t_prompt;

typedef struct s_word
{
	int				id;
	char			*content;
	struct s_word	*next;
}t_word;

typedef struct s_blank
{
	int				id;
	char			*content;
	struct s_blank	*next;
}t_blank;

typedef struct s_arg
{
	int				id;
	char			*content;
	struct s_arg	*next;
}t_arg;
// typedef int(*t_builtin_ptr)(t_llist *, t_info *);

// typedef struct s_info
// {
// 	// t_builtin_ptr	builtin[7];
// 	char			reserved_words[7];
// 	char			**envp;
// 	struct s_list	envp_list;
// 	char			envp_flag;
// 	char			exit_flag;
// 	int				status;

// }t_info;

t_list	*init_token(void);
t_cmd	*init_cmd(void);
t_word	*init_word(char *content, int id);
t_blank	*white_space(char *content, int id);
t_arg	*args(char *content, int id);
t_list	*create_token(char *content, int id);
void	prompt(char	*line);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);


#endif