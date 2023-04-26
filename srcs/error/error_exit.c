#include "../../headers/minishell.h"

// int	error(const char *title, const char *msg)
// {
// 	if (title && *title)
// 		printf(R "error: %s: %s\n" RS, title, msg);
// 	else
// 		dprintf(R "error: %s\n" RS, msg);
// 	if (errno)
// 		errno = 0;
// 	return (0);
// }

// void	msg_error(char *error, int errnum)
// {
// 	if (error)
// 	{
// 		ft_putstr_fd(error, STDERR_FILENO);
// 	}
// 	else
// 	{
// 		ft_putstr_fd(strerror(errnum), STDERR_FILENO);
// 		ft_putchar_fd('\n', STDERR_FILENO);
// 	}
// 	exit(errnum);
// }

void	msg_error(char *error, int errnum)
{
	if (error)
	{
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		// printf("errno: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd(strerror(errnum), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		// printf("errno: %d/n", errno);
	}

	// print the exit status to STDERR
	ft_putstr_fd("Exit status: ", STDERR_FILENO);
	ft_putnbr_fd(errnum, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	// printf("errno: %d\n", errno);


	exit(errnum);
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
	// termios_fini();
	exit(1);
	return (0);
}
