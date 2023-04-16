#include"../../headers/minishell.h"

int ft_env(char **args, t_envnode **mini_env)
{
	(void)args;
	t_envnode *mini_envp = *mini_env;
	if(!mini_envp)
		return(0);
	print_mini_envp(mini_envp);
	return(0);
}
