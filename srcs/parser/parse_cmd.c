#include "../../headers/minishell.h"

static int	build_word_red_cmd(t_cmd **new_cmd, t_token *tok_h)
{
	while (tok_h != NULL)
	{
		if (tok_h->id == T_PP)
			break ;
		if (tok_h->id == T_RO || tok_h->id == T_RI \
		|| tok_h->id == T_ROA || tok_h->id == T_RHD)
		{
			ft_token_list_addback(&(*new_cmd)->cmd_red, \
			new_token(tok_h->content, tok_h->id));
			ft_token_list_addback(&(*new_cmd)->cmd_red, \
			new_token(tok_h->next->content, T_W));
			tok_h = tok_h->next;
		}
		else
			ft_token_list_addback(&(*new_cmd)->cmd_word, \
			new_token(tok_h->content, tok_h->id));
		tok_h = tok_h->next;
	}
	return (0);
}

static void	*build_cmd(t_cmd **cmd_list, t_cmd **cmd_tail, t_cmd **new_cmd)
{
	if ((*cmd_list) == NULL)
	{
		(*cmd_list) = (*new_cmd);
		(*cmd_tail) = (*new_cmd);
	}
	else
	{
		(*cmd_tail)->next = (*new_cmd);
		(*cmd_tail) = (*new_cmd);
	}
	return (0);
}

void	*build_cmd_list(t_token **tok_cmd_list)
{
	t_token	*tok_h;
	t_cmd	*cmd_list;
	t_cmd	*cmd_tail;
	t_cmd	*new_cmd;
	int		i;

	cmd_list = NULL;
	cmd_tail = NULL;
	new_cmd = NULL;
	i = 0;
	while (tok_cmd_list[i] != NULL)
	{
		tok_h = tok_cmd_list[i];
		new_cmd = init_cmd();
		if (build_word_red_cmd(&new_cmd, tok_h) == -1)
			return (0);
		build_cmd(&cmd_list, &cmd_tail, &new_cmd);
		i++;
	}
	return (cmd_list);
}
