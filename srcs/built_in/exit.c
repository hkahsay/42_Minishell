#include"../../headers/minishell.h"

	int ft_exit(char **args, t_envnode **mini_env)
	{
	int	i;

	i = 0;
	if (args != NULL)
	{
		i = ft_atoi(*args);
		printf("exit\n");
		// free(mini_env);
		exit (i);
	}
	else
	{
		printf("exit\n");
		free(mini_env);
		// exit (g_status);
	}
	return (0);
	}
