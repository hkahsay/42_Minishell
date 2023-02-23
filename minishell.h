/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:29:01 by vgejno            #+#    #+#             */
/*   Updated: 2023/02/23 19:35:38 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

// typedef int(*t_builtin_ptr)(t_llist *, t_info *);

typedef struct s_info
{
	// t_builtin_ptr	builtin[7];
	char			reserved_words[7];
	char			**envp;
	// struct s_list	envp_list;
	char			envp_flag;
	char			exit_flag;
	int				status;
	
}t_info;

typedef struct s_list
{
	void			*key;
	void			*value;
	struct s_list	*next;
}t_list;



#endif