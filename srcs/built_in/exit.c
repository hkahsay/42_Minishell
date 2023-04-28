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

		// To debug:
		// - Uncomment the fscanf line below
		// - In one terminal, run `export MallocStackLogging=1`
		// - In the same terminal, run `./minishell`
		// - In another terminal, run `leaks minishell`
		
		// fscanf(stdin, "c"); // wait for user to enter input from keyboard
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
