#include "../../headers/minishell.h"

static int	ft_red_list_size(t_token **tok_head)
{
	t_token *tok_h;
	int		size;

	tok_h = *tok_head;
	size = 0;
	while (tok_h != NULL)
	{
		if (tok_h != NULL && (tok_h->id == TOK_REDIR_IN || tok_h->id == TOK_REDIR_OUT ||
			tok_h->id == TOK_REDIR_OUT_APPEND || tok_h->id == TOK_HEREDOC))
			size++;
		tok_h = tok_h->next;
	}
	return (size);
}

int	ft_handle_redir_all(t_ppline **new_ppline, t_token *ptr_cmd_red)
{
	t_token *red_ptr;
	red_ptr = ptr_cmd_red;

	int	red_list_size = ft_red_list_size(&red_ptr);
	(void)red_list_size;
	// printf(GOLD "Redir_list size: %d\n" RS, red_list_size);

		if (red_ptr->id == TOK_REDIR_OUT)
		{
			// printf(GOLD "Redir_out\n" RS);
			ft_handle_redir_out(new_ppline, &ptr_cmd_red);
		}
		if (red_ptr->id == TOK_REDIR_OUT_APPEND)
		{
			// printf(GOLD "Redir_out_append\n" RS);
			ft_handle_redir_append(new_ppline, &ptr_cmd_red);
		}
		if (red_ptr->id == TOK_REDIR_IN)
		{
			// printf(GOLD "Redir_in\n" RS);
			ft_handle_redir_in(new_ppline, &ptr_cmd_red);
		}
		if (red_ptr->id == TOK_HEREDOC)
		{
			// printf(GOLD "Redir_heredoc\n" RS);
			(*new_ppline)->pp_heredoc_status = 1;
			ft_handle_heredoc(new_ppline, &ptr_cmd_red);
		}
	free_token_list(ptr_cmd_red);
	return (1);
}
