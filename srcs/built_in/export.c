#include "../../headers/minishell.h"

t_envnode	*envdup(t_envnode *prev, t_envnode **mini_env)
{
	t_envnode	*node;

	if (!(*mini_env))
		return (NULL);
	node = create_mini_envvar_node((*mini_env)->key, (*mini_env)->value, (*mini_env)->content);
	if (!node)
		return (NULL);
	node->prev = prev;
	if ((*mini_env)->next)
	{
		node->next = envdup(node, &(*mini_env)->next);
		if (!node->next)
		{
			while (node->prev)
				node = node->prev;
			return (NULL);
		}
	}
	return (node);
}

t_envnode	*export_no_cmd(t_envnode **mini_env)
{
	return (envdup(NULL, mini_env));
}

static int	ft_export_noargs(t_envnode **mini_env, char **cmd_args, t_envnode *new_env)
{
		printf(YELLOW"only expo\n"RS);
		new_env = export_no_cmd(mini_env);
		if (!new_env)
		{
			printf(YELLOW"new_env\n"RS);
			return (-1);
		}
		// printf("content beginning: %s\n", (new_env)->content);
		ft_envnode_sort(&new_env);
		print_ex_sorted_envp(new_env, cmd_args);
		// print_mini_envp(new_env);
		printf(YELLOW"only expo\n"RS);
		return (0);
}

static int export_all(t_envnode **mini_env, char **cmd_args)
{
		char	*new_key;
		char	*new_value;
		char	*new_content;
		int		i;
		int j;

		i = 0;
		new_content = cmd_args[1];
		// printf(R "new_content %s\n" RS, new_content);
		while (cmd_args[1][i] != '=')
			i++;
		new_key = ft_substr((char *)cmd_args[1], 0, i);
		i++;
		j = 0;
		while (cmd_args[1][j] != '\0')
			j++;
		new_value = ft_substr((char *)cmd_args[1], i, j);
		if (!ft_setenv(new_key, new_value, new_content, mini_env))
			return (-1);
		return (0);
}

static int export_only_key(t_envnode **mini_env, char **cmd_args)
{
	char	*new_key;
	char	*new_value;
	// int		i;
	t_envnode *new_env_var; //new_env_var = NULL;

	// i = 0;
	new_key = ft_strdup(cmd_args[1]);
	new_env_var = find_env_var(new_key, mini_env);
	// printf(GREEN"there is != sign\n"RS);
	if (new_env_var)
		return (0);
	else
	{
		new_value = "";
		new_env_var = create_mini_envvar_node(new_key, new_value, new_key);
		if (!new_env_var)
			printf("no new_env_var\n");
		ft_add_envlist(new_env_var, mini_env);
	}
	return (0);
}

int ft_export(char **cmd_args, t_envnode **mini_env)
{
    t_envnode *new_env_var;

	new_env_var = NULL;
	if (cmd_args[1] == NULL && mini_env)
	{
		if (!ft_export_noargs(mini_env, cmd_args, new_env_var))
			return (-1);
	}
	if (cmd_args[1] && ft_strchr(cmd_args[1], '='))
	{
		if (!export_all(mini_env, cmd_args))
			return (-1);
	}
	if (cmd_args[1] && !ft_strchr(cmd_args[1], '='))
	{
		if (!export_only_key(mini_env, cmd_args))
			return (-1);
		// printf(R"print all cmd_args and return new prompt\n"RS);
	}
    return (0);
}

