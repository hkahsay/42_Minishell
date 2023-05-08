#include"../../headers/minishell.h"

int ft_setenv(char *name, char *value, char *content, t_envnode **env)
{
	t_envnode *var = find_env_var(name, env);

	if (var)
	{
		// Variable already exists, update its value
		my_free(var->value);
		var->value = ft_strdup(value);
		my_free(var->content);
		var->content = ft_strdup(content);
	}
	else
	{
		// printf(R"OK\n"RS);
		// Variable does not exist, add it to the list
		t_envnode *new_var = create_mini_envvar_node(name, value, content);
		// printf(R "%s\n" RS,content);
		ft_add_envlist(new_var, env);
	}
	return (0);  // Success
}

int	home_not_set(char *home, char *pwd)
{
	if (home == NULL || pwd == NULL)
	{
		// printf("Home is not set\n");
		return (0);
	}
	return (-1);
}
