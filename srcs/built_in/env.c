#include"../../headers/minishell.h"

int ft_env(t_ppline **ppline) //char **args, t_envnode **mini_env
{
	// (void)args;
	t_envnode *mini_envp = (*ppline)->pp_list_env;
	if(!mini_envp)
		return(0);
	print_mini_envp(mini_envp);
	return(EXIT_SUCCESS);
}
