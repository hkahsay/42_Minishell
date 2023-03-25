#include"../headers/minishell.h"

// int	check_built_in(char **arg)
// {
// 	if (strcmp(arg[0], "cd\n" == 0)
// 		|| strcmp(arg[0], "pwd\n" == 0)
// 		|| strcmp(arg[0], "echo\n" == 0)
// 		|| strcmp(arg[0], "export\n" == 0)
// 		|| strcmp(arg[0], "unset\n" == 0)
// 		|| strcmp(arg[0], "env\n" == 0)
// 		|| strcmp(arg[0], "exit\n" == 0))
// 		return (0);
// 	else
// 	{
// 		perror("command not found");
// 		return(1);
// 	}
// }

int	b_cd(t_envnode *list, char *input)
{
	if (strcmp(input, "cd") == 0)
	{
		printf("%s\n", find_env_name(list, "HOME"));
	}
	else if (strcmp(input, "~") == 0)
	{
		printf("%s\n", find_env_name(list, "HOME"));
	}
	// else if (strncmp(input, "cd ..", 5) == 0)
	// {
	// 	parse_cd(list, input);
	// }
	else 
		printf("Command not found: %s\n", input);
	return (0);
}


// int	check_built_in(t_envnode *list, char *path)
// {
// 	if (path == "cd\n")
// 			b_cd(list, path);
// 	if (path == "pwd")
// 	{
// 		mini_pwd2(list);
// 		// || strcmp(arg[0], "echo\n" == 0)
// 		// || strcmp(arg[0], "export\n" == 0)
// 		// || strcmp(arg[0], "unset\n" == 0)
// 		// || strcmp(arg[0], "env\n" == 0)
// 		// || strcmp(arg[0], "exit\n" == 0))
// 		return (0);

// 	}
// 	else
// 	{
// 		perror("command not found");
// 		return(1);
// 	}
// }

// void	cd(t_envnode *curr_var, char *path)
// {
// 	char *norm_path;
// 	char 		*pwd;
// 	size_t		pwd_len;
// 	size_t		path_len;
// 	// char		*old_pwd;
// 	char		*new_dir;

// 	if (path == 0 || path[0] == '~')
// 	{
// 		curr_var = find_env_name(curr_var, "HOME");
// 		if (curr_var == 0)
// 			ft_error("cd: HOME is not set");
// 		//absolute path
// 		norm_path = normalize_path(curr_var->value);
// 	}
// 	else if (path[0] == '/')
// 		norm_path = normalize_path(path);
// 	else
// 	{
// 		//relative path
// 		curr_var = find_env_name(curr_var, "PWD");
// 		if (curr_var == 0)
// 			ft_error("cd: PWD is not set");
// 		pwd = curr_var->value;
// 		pwd_len = strlen(pwd);
// 		path_len = strlen(path);
// 		new_dir = (char *)malloc(sizeof(pwd_len + path_len + 2));
// 		// snprintf(buf, pwd_len + path_len + 2, "%s/%s", pwd, path);
// 		printf("%s %s",pwd, path);
// 		norm_path = normalize_path(new_dir);
// 		free(new_dir);		
// 	}
// 	if (chdir(norm_path) != 0)
// 		ft_error("cd: failed to change directory");
// }