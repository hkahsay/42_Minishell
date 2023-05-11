#include"../../headers/minishell.h"

int	ft_exit(t_ppline **ppline)
{
	int	i;

	i = 0;
	if ((*ppline)->ppline_cmd != NULL)
	{
		i = ft_atoi(*(*ppline)->ppline_cmd);
		printf("exit\n");
		destroy_all();
		exit (i);
	}
	else
	{
		printf("exit\n");
		destroy_all();
		exit (g_exit_status);
	}
	return (0);
}
