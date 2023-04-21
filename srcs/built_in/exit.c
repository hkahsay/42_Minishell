#include"../../headers/minishell.h"

	int ft_exit(char **args, t_envnode **mini_env)
	{
	int	i;

	i = 0;
	(void)mini_env;
	if (args != NULL)
	{
		i = ft_atoi(*args);
		// free_mini_envp(*mini_env);
		// free(mini_env);
		destroy_all();
		exit (i);
	}
	else
	{
		// free(mini_env);
		destroy_all();
		// exit (g_status);
	}
	return (0);
	}


// int ft_exit(char **args, t_envnode **env_var)
// {
//     (void)args;
//     (void)env_var;
//     printf("ft_exit\n");
//     return 0;
// }
