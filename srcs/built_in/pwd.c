#include"../../headers/minishell.h"

//The buffer size of 4096 is commonly used as
//a default value for storing the current working directory
// path because it is a multiple of the typical filesystem
//block size (e.g., 512 or 1024 bytes), and it is a power of two.

int ft_pwd(t_ppline **ppline) //char **args, t_envnode **mini_env
{
	t_envnode	*curr_var;
	char		*cwd;
	t_envnode	*env_var;

	env_var = NULL;
	cwd = getcwd(NULL, 0);
	curr_var = (*ppline)->pp_list_env;
	if ((*ppline)->ppline_cmd[1])
	{
		printf("too many arguments\n");
		exit(0);
	}
	while(curr_var != 0 && (*ppline)->ppline_cmd[1] == 0 )
	{
		// printf("b %s\n", curr_var->value);
		if (ft_strcmp(curr_var->key, "pwd") == 0 || ft_strcmp(curr_var->key, "PWD") == 0)
		{
			if(ft_strcmp(curr_var->value, cwd) == 0)
			{
				printf("get pwd %s\n", curr_var->value);
				return (0);
			}
			else
			{
				my_free(curr_var->value);
				curr_var->value = strdup(cwd);
				printf("%s\n", curr_var->value);
				return(0);
			}
		}
		curr_var = curr_var->next;
	}
	return 0;
}
