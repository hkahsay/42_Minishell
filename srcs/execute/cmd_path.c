#include "../../headers/minishell.h"

char	*find_path(char **mini_env_array)
{
	while (ft_strncmp("PATH", *mini_env_array, 4))
		mini_env_array++;
	return (*mini_env_array + 5);
}

int	search_path(t_ppline *ppline, char **cmd_path) //, char **mini_env_array
{
	char	**path_array;
	int		i;
	char	*temp;

	i = 0;
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
