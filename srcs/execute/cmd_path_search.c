#include "../../headers/minishell.h"

static int	search_path_array(t_ppl *ppl, char **cmd_path)
{
	char	**path_array;
	char	*temp;
	int		i;

	i = 0;
	path_array = ft_split(*cmd_path, ':');
	while (path_array[i])
	{
		temp = ft_strjoin(path_array[i], "/");
		*cmd_path = ft_strjoin(temp, ppl->ppl_cmd[0]);
		if (!access(*cmd_path, F_OK))
			return (-1);
		i++;
	}
	return (0);
}

static int	check_curr_dir(t_ppl *ppl, char **cmd_path, \
char *instance, char **mini_path)
{
	if (ft_strncmp(instance, ppl->pp_first_cmd, ft_strlen(instance)) == 0)
	{
		if (find_curr_dir(mini_path) == 0)
		{
			*cmd_path = ft_strdup(*mini_path);
			printf("4. cmd_path %s\n", *cmd_path);
			if (!access(*cmd_path, F_OK) && !access(*cmd_path, X_OK))
				return (-1);
		}
		return (0);
	}
	return (0);
}

int	search_path(t_ppl *ppl, char **cmd_path)
{
	char	*instance;
	char	*mini_path;

	instance = "./minishell";
	mini_path = NULL;
	if (check_curr_dir(ppl, cmd_path, instance, &mini_path) == -1)
	{
		
		return (-1);
	}
	*cmd_path = find_path(ppl->pp_arr_env);
	if (search_path_array(ppl, cmd_path) == -1)
		return (-1);
	return (0);
}
