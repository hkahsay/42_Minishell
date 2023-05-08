#include "../../headers/minishell.h"

void	handle_input_error(t_token **token_head)
{
	t_token *tok_h;

	tok_h = *token_head;
	if (tok_h != NULL && tok_h->id == TOK_PIPE)
	{
		ft_putstr_fd("ERROR input PIPE 1\n", STDERR_FILENO);
		g_exit_status = 258;
		printf("g_exit_status: %d\n", g_exit_status);
		return ;
		// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
	}
	while (tok_h != NULL)
	{
		if (tok_h->id == TOK_PIPE && tok_h->next && tok_h->next->id == TOK_PIPE)
			// g_exit_status = 1;
		{
			ft_putstr_fd("ERROR input PIPE 2\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
			// tok_h->id = TOK_ERROR;
			return ;
		}
		if (tok_h != NULL && last_token(tok_h)->id == TOK_PIPE)
		{
			ft_putstr_fd("ERROR input PIPE 3\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 1); //syntax error (near unexpected token `|')

			// ft_putstr_fd("ERROR input last PIPE\n", STDERR_FILENO);
			// tok_h->id = TOK_ERROR;
			return ;
		}
		else
			tok_h = tok_h->next;
	}
}
