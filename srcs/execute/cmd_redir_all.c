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

int	ft_handle_redir_all(t_ppl **new_ppl, t_token *ptr_cmd_red)
{
	int	i;

	i = 0;
	int	red_list_size = ft_red_list_size(&ptr_cmd_red);
	while (ptr_cmd_red && i < red_list_size)
	{
		if (ptr_cmd_red->id == TOK_REDIR_OUT)
			ft_handle_redir_out(new_ppl, &ptr_cmd_red);
		if (ptr_cmd_red->id == TOK_REDIR_OUT_APPEND)
			ft_handle_redir_append(new_ppl, &ptr_cmd_red);
		if (ptr_cmd_red->id == TOK_REDIR_IN)
		{
			// ft_handle_redir_in(new_ppl, &ptr_cmd_red);
			if (ft_handle_redir_in(new_ppl, &ptr_cmd_red) == 1)
				return (1);
			else
			{
				printf(GREEN "error\n" RS);
				return (-1);
			}
			// if (ft_handle_redir_in(new_ppl, &ptr_cmd_red) == 0)
			// 	return (1);
			// return (0);
		}
		if (ptr_cmd_red->id == TOK_HEREDOC)
		{
			(*new_ppl)->pp_heredoc_status = 1;
			ft_handle_heredoc(new_ppl, &ptr_cmd_red);
		}
		if (ptr_cmd_red->next->next)
			ptr_cmd_red = ptr_cmd_red->next->next;
		i++;
	}
	free_token_list(ptr_cmd_red);
	return (1);
}
