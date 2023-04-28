#include "../../headers/minishell.h"

char	*find_path(char **mini_env_array)
{
	printf(SILVER "Find path\n" RS);
	// print_mini_env_array(new_ppline->pp_arr_env);
	while (ft_strncmp("PATH", *mini_env_array, 4))
		mini_env_array++;
	// printf(SILVER "Found path\n" RS);
	// if (mini_env_array == NULL)
	// 	return (NULL);
	return (*mini_env_array + 5);
}

int	search_path(t_ppline *ppline, char **cmd_path) //, char **mini_env_array
{
	printf(SILVER "Search path\n" RS);
	char	**path_array;
	int		i;
	char	*temp;

	i = 0;
	// print_mini_env_array(ppline->pp_arr_env);
	*cmd_path = find_path(ppline->pp_arr_env);
	// if (!*cmd_path)
	// {
	// 	msg_error(ft_strjoin("minishell: command not found: ", ppline->pp_first_cmd), errno);
	// 	// printf(R "NO PATH\n" RS);
	// 	// return (-1);

	// }
	printf(R "*cmd_path: %s\n" RS, *cmd_path);
	path_array = ft_split(*cmd_path, ':');
	i = 0;
	while (path_array[i])
	{
		temp = ft_strjoin(path_array[i], "/");
		*cmd_path = ft_strjoin(temp, ppline->ppline_cmd[0]);
		my_free(temp);
		if (!access(*cmd_path, F_OK))
		{
			// msg_error(ft_strjoin("minishell: command not found: ", ppline->pp_first_cmd), errno);
			return (-1);
		}
		i++;
	}
	// if (!*cmd_path)
	// {
	// 	msg_error(ft_strjoin("minishell: command not found: ", ppline->pp_first_cmd), errno);
	// 	// printf(R "NO PATH\n" RS);
	// 	// return (-1);

	// }
	return (0);
}
