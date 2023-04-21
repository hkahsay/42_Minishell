#include"../../headers/minishell.h"

int ft_pwd(char **args, t_envnode **mini_env)
{
	t_envnode	*curr_var;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	curr_var = *mini_env;
	if (args[1])
	{
		printf("too many arguments\n");
		exit(0);
	}
	while(curr_var != 0 && args[1] == 0 )
	{
		// printf("b %s\n", curr_var->value);
		if (ft_strcmp(curr_var->key, "pwd") == 0 || ft_strcmp(curr_var->key, "PWD") == 0)
		{
			if(ft_strcmp(curr_var->value, cwd) == 0)
			{
				printf("%s\n", curr_var->value);
				return (0);
			}
			else
			{
				free(curr_var->value);
				curr_var->value = strdup(cwd);
				printf("%s\n", curr_var->value);
				return(0);
			}
		}
		curr_var = curr_var->next;
	}
	return 0;
}