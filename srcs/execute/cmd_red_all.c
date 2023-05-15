#include "../../headers/minishell.h"

static int	ft_red_list_size(t_token **tok_head)
{
	t_token	*tok_h;
	int		size;

	tok_h = *tok_head;
	size = 0;
	while (tok_h != NULL)
	{
		if (tok_h != NULL && (tok_h->id == T_RI || tok_h->id == T_RO \
		|| tok_h->id == T_ROA || tok_h->id == T_RHD))
			size++;
		tok_h = tok_h->next;
	}
	return (size);
}

static int	handle_redirection(t_ppl **new_ppl, t_token **ptr_cmd_red)
{
	if ((*ptr_cmd_red)->id == T_RO)
	{
		if (ft_handle_redir_out(new_ppl, ptr_cmd_red) == 1)
			return (1);
		else
			return (0);
	}
	else if ((*ptr_cmd_red)->id == T_ROA)
	{
		return (ft_handle_redir_append(new_ppl, ptr_cmd_red) == 1);
		if (ft_handle_redir_append(new_ppl, ptr_cmd_red) == 1)
			return (1);
		else
			return (0);

	}
	else if ((*ptr_cmd_red)->id == T_RI)
	{
		if (ft_handle_redir_in(new_ppl, ptr_cmd_red) == 1)
			return (1);
		else
			return (0);
	}
	else if ((*ptr_cmd_red)->id == T_RHD)
	{
		(*new_ppl)->pp_heredoc_status = 1;
		ft_handle_heredoc(new_ppl, ptr_cmd_red);
	}
	return (1);
}

int	ft_handle_red_all(t_ppl **new_ppl, t_token *ptr_cmd_red)
{
	int	i;
	int	red_list_size;

	i = 0;
	red_list_size = ft_red_list_size(&ptr_cmd_red);
	while (ptr_cmd_red && i < red_list_size)
	{
		if (!handle_redirection(new_ppl, &ptr_cmd_red))
			return (0);
		if (ptr_cmd_red->next->next)
			ptr_cmd_red = ptr_cmd_red->next->next;
		i++;
	}
	free_token_list(ptr_cmd_red);
	return (1);
}
