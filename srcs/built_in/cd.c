#include"../../headers/minishell.h"

int	ft_cd(char **args, t_envnode **mini_env)
{
	char cwd[1024];

	t_envnode	*env_var = NULL;
	if (!args[1])
	{
		env_var = find_env_var("HOME", mini_env);
		if (!env_var)
		{
			fprintf(stderr, "cd: HOME environment variable not set\n");
			return (1);
		}
	}
	else
	{
		if (chdir(args[1]))
		{
			perror("cd");
			return (1);
		}
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return 1;
	}
	ft_setenv("PWD", cwd, (*mini_env)->content, &env_var);
	printf ("env_var%s\n", env_var->value);
	return (0);
}


