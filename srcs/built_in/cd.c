#include"../../headers/minishell.h"

// int	ft_cd(t_ppline	**ppline) //char **args, t_envnode **mini_env
// {
// 	char cwd[4096];

// 	t_envnode	*env_var = NULL;
// 	if (!args[1])
// 	{
// 		env_var = find_env_var("HOME", ppline->); //mini_env
// 		if (!env_var)
// 		{
// 			fprintf(stderr, "cd: HOME environment variable not set\n");
// 			return (1);
// 		}
// 	}
// 	else
// 	{
// 		if (chdir(args[1]))
// 		{
// 			perror("cd");
// 			return (1);
// 		}
// 	}
// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 	{
// 		perror("getcwd");
// 		return 1;
// 	}
// 	ft_setenv("PWD", cwd, (*mini_env)->content, &env_var);
// 	printf ("env_var%s\n", env_var->value);
// 	return (0);
// }


int	ft_cd(t_ppline **ppline) //char **args, t_envnode **mini_env
{
	char cwd[4096];
	t_envnode	*env_var;

	env_var = NULL;
	if (!(*ppline)->ppline_cmd[1]) //args[1]
	{
		env_var = find_env_var("HOME", &(*ppline)->pp_list_env);
		if (!env_var)
		{
			fprintf(stderr, "cd: HOME environment variable not set\n");
			return (1);
		}
	}
	else
	{
		if (chdir((*ppline)->ppline_cmd[1]))
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
	ft_setenv("PWD", cwd, (*ppline)->pp_list_env->content, &env_var);
	printf ("env_var%s\n", env_var->value);
	return (0);
}
