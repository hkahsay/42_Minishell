#include "../../headers/minishell.h"

int	handle_input_pipe(void)
{
	ft_putstr_fd("minishell_VH: syntax error near unexpected token `|\'\n" \
	, STDERR_FILENO);
	g_exit_status = 258;
	return (EXIT_SUCCESS);
}

int	handle_input_2pipes(void)
{
	ft_putstr_fd("minishell_VH: syntax error near unexpected token `||\'\n", \
	STDERR_FILENO);
	g_exit_status = 258;
	return (EXIT_SUCCESS);
}

int	handle_input_red_error(void)
{
	ft_putstr_fd("minishell_VH: syntax error near unexpected token `newline'\n" \
	, STDERR_FILENO);
	g_exit_status = 258;
	return (EXIT_SUCCESS);
}

int	handle_input_red_pipe(char **content)
{
	char	*msg;

	msg = NULL;
	msg = ft_strjoin("minishell_VH: syntax error near unexpected token `", \
	*content);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\'\n", STDERR_FILENO);
	g_exit_status = 258;
	return (EXIT_SUCCESS);
}
