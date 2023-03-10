/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkahsay <hkahsay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:15:44 by hkahsay           #+#    #+#             */
/*   Updated: 2023/03/10 12:16:24 by hkahsay          ###   ########.fr       */
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
# define REDIR_OUT 2
# define REDIR_IN 3
# define REDIR_APPEND 4
# define HERE_DOC 5
# define PIPE 6

typedef struct s_list
{
	int				id_token;
	char			*content;
	struct s_list	*next;

}	t_list;

typedef struct s_prompt
{
	int			nbr_elm;
	char		*str;
}	t_prompt;

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
t_list	*create_token(char *content, int id);
void	prompt(char	*line);
// int		ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);
char	*classification(t_list *token, char *content, int id);
char	*word_token(char *word);
int		is_word(const char *str);
t_list	*create_token(char *content, int id);
int	is_space(char c);
char	**ft_split(const char *s, char c);
int	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);






#endif