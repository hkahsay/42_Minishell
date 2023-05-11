#include "../../headers/minishell.h"

void	msg_error(char *error, int errnum)
{
	g_exit_status %= 256;
	if (error)
	{
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd(strerror(errnum), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	ft_putstr_fd("Exit status: ", STDERR_FILENO);
	ft_putnbr_fd(g_exit_status, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(g_exit_status);
}

int	error_msg(const char *msg)
{
	printf(R "error: %s\n" RS, msg);
	if (errno)
		errno = 0;
	return (0);
}

int	error_mem(void)
{
	error_msg("memory");
	exit(1);
	return (0);
}
