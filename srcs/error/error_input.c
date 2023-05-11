#include "../../headers/minishell.h"

int	handle_input_error(t_token **token_head)
{
	t_token *tok_h;
	char	*msg;

	tok_h = *token_head;
	if (tok_h != NULL && tok_h->id == TOK_PIPE)
	{
		// ft_putstr_fd("ERROR input PIPE 1\n", STDERR_FILENO);
		// msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", "|");
		ft_putstr_fd("minishell_VH: syntax error near unexpected token `|\'\n", STDERR_FILENO);
		// ft_putstr_fd(msg, STDERR_FILENO);
		// ft_putstr_fd("\'\n", STDERR_FILENO);
		g_exit_status = 258;
		// printf("g_exit_status: %d\n", g_exit_status);
		return (1);
		// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
	}
	while (tok_h != NULL)
	{
		if (tok_h && tok_h->id == TOK_PIPE && tok_h->next && tok_h->next->id == TOK_PIPE)
			// g_exit_status = 1;
		{
			// ft_putstr_fd("minishell_VH: syntax error near unexpected token `", STDERR_FILENO);
			// ft_putstr_fd(tok_h->content, STDERR_FILENO);
			// msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", tok_h->content);
			// ft_putstr_fd(msg, STDERR_FILENO);
			// ft_putstr_fd("\'\n", STDERR_FILENO);
			ft_putstr_fd("minishell_VH: syntax error near unexpected token `||\'\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
			// tok_h->id = TOK_ERROR;
			return (1);
		}
		if (tok_h != NULL && last_token(tok_h)->id == TOK_PIPE)
		{
			// ft_putstr_fd("minishell_VH: syntax error near unexpected token `", STDERR_FILENO);
			// msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", tok_h->content);
			// ft_putstr_fd(msg, STDERR_FILENO);
			// ft_putstr_fd("\'\n", STDERR_FILENO);
			ft_putstr_fd("minishell_VH: syntax error near unexpected token `|\'\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 1); //syntax error (near unexpected token `|')

			// ft_putstr_fd("ERROR input last PIPE\n", STDERR_FILENO);
			// tok_h->id = TOK_ERROR;
			return (1);
		}
		if (tok_h != NULL && tok_h->id == TOK_ERROR)
		{
			// ft_putstr_fd("minishell_VH: syntax error near unexpected token `", STDERR_FILENO);
			msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", tok_h->content);
			ft_putstr_fd(msg, STDERR_FILENO);
			ft_putstr_fd("\'\n", STDERR_FILENO);
			g_exit_status = 258;
			// msg_error("error near unexpected token", 258); //syntax error (near unexpected token `|')
			// tok_h->id = TOK_ERROR;
			return (1);
		}
		else
			tok_h = tok_h->next;
	}
	return (0);
}
