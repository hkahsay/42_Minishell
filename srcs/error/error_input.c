#include "../../headers/minishell.h"

void	handle_input_error(t_token **token_head)
{
	t_token *tok_h;

	tok_h = *token_head;
	if (tok_h != NULL && tok_h->id == TOK_PIPE)
			ft_putstr_fd("ERROR input PIPE\n", STDERR_FILENO); //syntax error (near unexpected token `|')
	while (tok_h != NULL)
	{
		if (tok_h->id == TOK_PIPE && tok_h->next && tok_h->next->id == TOK_PIPE)
		{
			ft_putstr_fd("ERROR input PIPE\n", STDERR_FILENO);
			tok_h->id = TOK_ERROR;
			// return ;
		}
		if (tok_h != NULL && last_token(tok_h)->id == TOK_PIPE)
		{
			ft_putstr_fd("ERROR input last PIPE\n", STDERR_FILENO);
			tok_h->id = TOK_ERROR;
			// return ;
		}
		tok_h = tok_h->next;
	}	
}