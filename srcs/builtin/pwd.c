#include"../headers/minishell.h"

// int	mini_pwd(void)
// {
// 	char	*buf;

// 	buf = getcwd(NULL, 0);
// 	ft_putendl_fd(buf, 1);
// 	free(buf);
// 	return (0);
// }
int	mini_pwd2(t_envnode *env_list)
{
	t_envnode	*curr_var;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	curr_var = env_list;
	while (curr_var != 0)
	{
		if (strcmp(curr_var->key, "PWD") == 0)
		{
			if (strcmp(curr_var->value, cwd) == 0)
			{
				printf("%s\n", curr_var->value);
				return (0);
			}
			else
			{
				free(curr_var->value);
				curr_var->value = strdup(cwd);
				printf("%s\n", curr_var->value);
				return (0);
			}
		}
		curr_var = curr_var->next;
	}
	return (0);
}
//get our absolute current working directory with getcwd function
//traverse env linked list to find pwd variable
// compare env var if PWD is exist 
//if it exist compare the value with cwd
// if it is the same printf env_var->value,if not
//free curr_var then change or modify the value with cwd

