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

	cwd = (char *)malloc(PATH_MAX * sizeof(char));
	if (cwd != NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			free(cwd);
			cwd = NULL;
		}
	}
	return (cwd);
}

static int	find_current_directory(char **path)
{
	char *curr_dir;

	curr_dir = NULL;
	curr_dir = get_current_directory();
	if (curr_dir != NULL)
	{
		*path = (char *)malloc((strlen(curr_dir) + ft_strlen("/minishell") + 1) * sizeof(char));
		if (*path != NULL)
		{
			ft_strlcpy(*path, curr_dir, (strlen(curr_dir) + 1));
			*path = ft_strjoin(*path, "/minishell");
		}
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
	if (ft_strncmp(instance, ppline->pp_first_cmd, ft_strlen(instance)) == 0)
	{
		if (find_current_directory(&minishell_path) == 0)
		{
			*cmd_path = ft_strdup(minishell_path);
			if (!access(*cmd_path, F_OK) && !access(*cmd_path, X_OK))
				return (-1);
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
		my_free(temp);
		if (!access(*cmd_path, F_OK))
			return (-1);
		i++;
	}
	return (0);
}
