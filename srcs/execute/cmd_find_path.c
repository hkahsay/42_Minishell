#include "../../headers/minishell.h"

char	*find_path(char **mini_env_array)
{
	while (ft_strncmp("PATH", *mini_env_array, 4))
		mini_env_array++;
	return (*mini_env_array + 5);
}

static char	*get_current_directory(void)
{
	char *cwd;

	cwd = (char *)my_malloc(PATH_MAX * sizeof(char));
	printf(R "cwd %p\n" RS, cwd);
	if (cwd != NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			printf("1. if getcwd get_current_directory: cwd %s\n", cwd);
			// my_free(cwd);
			cwd = NULL;
		}
	}
	printf("get_current_directory: cwd %s\n", cwd);
	return (cwd);
}

static int	find_current_directory(char **path)
{
	char *current_directory = NULL;
	// char *executable_path = NULL;

	current_directory = get_current_directory();
	printf("2. current_directory %s\n", current_directory);
	if (current_directory != NULL)
	{
		*path = (char *)my_malloc((strlen(current_directory) + ft_strlen("/minishell") + 1) * sizeof(char));
		printf(R "path %p\n" RS, path);
		if (*path != NULL)
		{
			ft_strlcpy(*path, current_directory, (ft_strlen(current_directory) + 1));
			printf("3. *path1 %s\n", *path);
			*path = ft_strjoin(*path, "/minishell");
			printf("3. *path2 %s\n", *path);
			// if (!access(*path, X_OK))
			// {
			// 	printf("3. !access(*path, X_OK)\n");
			// 	return (-1);
			// }
			// my-free(executable_path);
		}
		// my-free(current_directory);
	}
	return (0);
}

int	search_path(t_ppline *ppline, char **cmd_path)
{
	char	**path_array;
	char 	*instance = NULL;
	int		i;
	char	*temp = NULL;
	char	*minishell_path = NULL;

	i = 0;
	instance = "./minishell";
	// print_mini_env_array(ppline->pp_arr_env);
	if (ft_strncmp(instance, ppline->pp_first_cmd, ft_strlen(instance)) == 0)
	{
		printf("4. ok ./minishell\n");
		if (find_current_directory(&minishell_path) == 0)
		{
			printf("4. find_current_directory\n");
			*cmd_path = ft_strdup(minishell_path);
			printf("4. cmd_path %s\n", *cmd_path);
			// my_free(temp);
			// *cmd_path = minishell_path;
			// *cmd_path = ft_strjoin(minishell_path, ppline->ppline_cmd[0]);
			if (!access(*cmd_path, F_OK) && !access(*cmd_path, X_OK))
			{
				printf("3. !access(*path, X_OK)\n");
				return (-1);
			}

		}
		return (0);
	}
	*cmd_path = find_path(ppline->pp_arr_env);
	path_array = ft_split(*cmd_path, ':');
	i = 0;
	while (path_array[i])
	{
		temp = ft_strjoin(path_array[i], "/");
		*cmd_path = ft_strjoin(temp, ppline->ppline_cmd[0]);
		if (!access(*cmd_path, F_OK))
		{
			return (-1);
		}
		i++;
	}
	printf("5. execve cmd_path %s\n", *cmd_path);
	return (0);
}
