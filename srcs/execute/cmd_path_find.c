#include "../../headers/minishell.h"

char	*find_path(char **mini_env_array)
{
	while (ft_strncmp("PATH", *mini_env_array, 4))
		mini_env_array++;
	return (*mini_env_array + 5);
}

static char	*get_curr_dir(void)
{
	char	*cwd;

	cwd = (char *)my_malloc(PATH_MAX * sizeof(char));
	if (cwd != NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			printf("1. if getcwd get_curr_dir: cwd %s\n", cwd);
			cwd = NULL;
		}
	}
	return (cwd);
}

int	find_curr_dir(char **path)
{
	char	*curr_dir;

	curr_dir = NULL;
	curr_dir = get_curr_dir();
	if (curr_dir != NULL)
	{
		*path = (char *)my_malloc((strlen(curr_dir) + \
		ft_strlen("/minishell") + 1) * sizeof(char));
		if (*path != NULL)
		{
			ft_strlcpy(*path, curr_dir, (strlen(curr_dir) + 1));
			*path = ft_strjoin(*path, "/minishell");
		}
	}
	return (0);
}
