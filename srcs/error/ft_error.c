#include "../../headers/minishell.h"

int	ft_error_print(char **arg)
{
	printf("Bash: ");
	printf("%s", arg[0]);
	printf(": ");
	printf("Command not found");
	printf("\n");
	g_exit_status = 127;
	return (1);
}