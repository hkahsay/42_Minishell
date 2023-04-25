#include "../../headers/minishell.h"

int	ft_handle_redir_all(t_ppline **new_ppline, t_token *ptr_cmd_red)
{
	// printf("redir\n");
	(void)new_ppline;
	t_token *red_ptr;
	// (void)ptr_cmd_red;
	red_ptr = ptr_cmd_red;
	if (red_ptr->id == TOK_REDIR_OUT)
	{
		ft_handle_redir_out(new_ppline, &ptr_cmd_red);
		return (1);
	}
	if (red_ptr->id == TOK_REDIR_OUT_APPEND)
	{
		ft_handle_redir_append(new_ppline, &ptr_cmd_red);
		return (1);
	}
	if (red_ptr->id == TOK_REDIR_IN)
	{
		ft_handle_redir_in(new_ppline, &ptr_cmd_red);
		return (1);
	}
	if (red_ptr->id == TOK_HEREDOC)
	{
		ft_handle_heredoc(new_ppline, &ptr_cmd_red);			
		return (1);
	}
	return (0);
}
