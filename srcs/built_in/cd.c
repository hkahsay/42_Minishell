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
        // if (chdir((const char *)env_var))
        // {
        //     perror("cd");
        //     return (1);
        // }
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



	// int	ft_cd(char **args, t_envnode **mini_env)
	// {
	// char cwd[1024];

	// t_envnode	*env_var = NULL;
	// if (!args[1])
	// {
	// 	env_var = find_env_var("HOME", mini_env);
	// 	if (!env_var)
	// 	{
	// 		fprintf(stderr, "cd: HOME environment variable not set\n");
	// 		return (1);
	// 	}
	// 	// if (chdir((const char *)env_var))
	// 	// {
	// 	//     perror("cd");
	// 	//     return (1);
	// 	// }
	// }
	// else
	// {
	// 	if (chdir(args[1]))
	// 	{
	// 		perror("cd");
	// 		return (1);
	// 	}
	// }
	// if (getcwd(cwd, sizeof(cwd)) == NULL)
	// {
	// 	perror("getcwd");
	// 	return 1;
	// }
	// ft_setenv("PWD", cwd, &env_var);
	// printf ("env_var%s\n", env_var->value);
	// return (0);
	// }

// int ft_cd(char **args, t_envnode **env_var)
// {
//     (void)args;
//     (void)env_var;
//     printf("ft_cd\n");
//     return 0;
// }

// int	ft_cd(char **args, t_envnode *env_list)
// {
// 	char	*path;
// 	// t_envnode	*pwd;
// 	// args = "cd";
// 	if (!args)
// 	{
// 		env_list = find_env_key("HOME", env_list);
// 		printf("env_list %s\n", env_list->value);
// 		if (ft_strlen(env_list->value) != 0)
// 		{
// 			path = env_list->value;
// 			printf("here1,env_list->value %s\n",  path);
// 		}
// 		else
// 		{
// 			printf("HOME is not set \n");
// 			return (1);
// 		}
// 	}
// 	else
// 		path = args[0];
// 	ft_setenv("PWD", path, &env_list);
// 	if (chdir(path) == -1)
// 	{
// 		if (access(path, F_OK) == -1)
// 			printf("bash: cd: %s: No such file or directory\n", path);
// 		else
// 			printf("bash: cd: %s: Not a directory\n", path);
// 	}
// 	// ft_setenv("PWD", env_list->value,  &env_list);
// 	// Change the current working directory and update PWD variable
// 	//  // Update the PWD and OLDPWD environment variables
//     // ft_setenv("OLDPWD", getenv("PWD"), 1);
//     // ft_setenv("PWD", getcwd(NULL, 0), 1);

//     // Return the updated environment variables
//     return (0);
// }


// int	b_cd(t_envnode *list, char *input)
// {
// 	if (strcmp(input, "cd") == 0)
// 	{
// 		printf("%s\n", find_env_name(list, "HOME"));
// 	}
// 	else if (strcmp(input, "~") == 0)
// 	{
// 		printf("%s\n", find_env_name(list, "HOME"));
// 	}
// 	// else if (strncmp(input, "cd ..", 5) == 0)
// 	// {
// 	// 	parse_cd(list, input);
// 	// }
// 	else
// 		printf("Command not found: %s\n", input);
// 	return (0);
// }


