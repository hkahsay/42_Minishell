#include"../../headers/minishell.h"

	int ft_exit(t_ppline **ppline) //char **args, t_envnode **mini_env
	{
	int	i;

	i = 0;
	// (void)mini_env;
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
