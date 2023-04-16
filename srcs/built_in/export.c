#include "../../headers/minishell.h"

t_envnode	*envdup(t_envnode *prev, t_envnode **mini_env)
{
	t_envnode	*node;

	if (!(*mini_env))
	{
		// printf(BLUE"1\n"RS);
		return (NULL);
	}
	node = create_mini_envvar_node((*mini_env)->key, (*mini_env)->value, (*mini_env)->content);
	// printf(BLUE"2\n"RS);
	if (!node)
	{
		// printf(BLUE"3\n"RS);
		return (NULL);
	}
	// printf(BLUE"4\n"RS);
	node->prev = prev;
	// printf(BLUE"5\n"RS);
	if ((*mini_env)->next)
	{
		// printf(BLUE"6\n"RS);
		node->next = envdup(node, &(*mini_env)->next);
		// printf(BLUE"7\n"RS);
		if (!node->next)
		{
			// printf(BLUE"8\n"RS);
			// printf(OR"OK\n"RS);
			while (node->prev)
			{
				// printf(BLUE"9\n"RS);
				node = node->prev;
			}
			// printf(BLUE"10\n"RS);
			// free_mini_envp(node);
			return (NULL);
		}
		// printf(BLUE"11\n"RS);
	}
	// printf(BLUE"12\n"RS);
	return (node);
}

t_envnode	*export_no_cmd(t_envnode **mini_env)
{
	return (envdup(NULL, mini_env));
}

// t_envnode *init_content(char *content)
// {
// 	t_envnode **mini_env = NULL;
// 	content = ft_strjoin((*mini_env)->key, (*mini_env)->value);
// 	printf("*mini_env)->content %s\n", (*mini_env)->content);
// 	return (*mini_env);
// }

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

static int fuck_export(t_envnode **mini_env, char **cmd_args)
{
		char	*new_key;
		char	*new_value;
		// char	*new_content;
		int		i;
		int j;
		// int k = 0;
		// t_envnode *new_env_var = NULL;
		i = 0;
		char	*new_content = cmd_args[1];
		printf(R "new_content %s\n" RS, new_content);
		// while (cmd_args[1][k])
		// {
		// 	k++;
		// }
		// new_content = ft_substr((char *)cmd_args[1], 0, k);
		while (cmd_args[1][i] != '=')
		{
			printf(BLUE "*cmd_args[1] %c\n"RS, cmd_args[1][i]);
			printf(R"there is == sign in key\n"RS);
			i++;
		}
		new_key = ft_substr((char *)cmd_args[1], 0, i);
		i++;
		j = 0;
		while (cmd_args[1][j] != '\0')
		{
			printf(GREEN"*cmd_args[1] %c\n"RS, cmd_args[1][j]);
			printf(OR"there is == sign in value\n"RS);
			j++;
		}
		new_value = ft_substr((char *)cmd_args[1], i, j);
		if (!ft_setenv(new_key, new_value, new_content, mini_env))
			return (-1);
		return (0);
}

static int fuck_only_key(t_envnode **mini_env, char **cmd_args)
{
	char	*new_key;
	char	*new_value;
	int		i;
	t_envnode *new_env_var = NULL;

	i = 0;
	printf("cmd_argher: %c\n", cmd_args[1][i]);
	new_key = ft_strdup(cmd_args[1]);
	new_env_var = find_env_var(new_key, mini_env);
	printf(GREEN"there is != sign\n"RS);
	if (new_env_var)
	{
		// If environment variable already exists, set its value to empty string
		// free(new_env_var->value);
		// new_env_var->value = ft_strdup("");//ft_strdup("");
		return (0);
	}
	else
	{
		// If environment variable does not exist, create a new one with empty value
		new_value = ""; //ft_strdup("");
		new_env_var = create_mini_envvar_node(new_key, new_value, new_key);
		if (!new_env_var)
			printf("no new_env_var\n");
		ft_add_envlist(new_env_var, mini_env);

	}
	return (0);
}

int ft_export(char **cmd_args, t_envnode **mini_env)
{
	// char	*new_key;
	// char	*new_value;
	// int		i;
    t_envnode *new_env_var = NULL;
	// t_cmd	*cmds = NULL;
	// int	len = 0;
	// i = 0;
	if (cmd_args[1] == NULL && mini_env)
	{ // export
		if (!ft_export_noargs(mini_env, cmd_args, new_env_var))
			return (-1);
	}
	if (cmd_args[1] && ft_strchr(cmd_args[1], '=')) //ft_strchr(const char	*s, int c)
	{ // export with key and value
		if (!fuck_export(mini_env, cmd_args))
			return (-1);
	}
	if (cmd_args[1] && !ft_strchr(cmd_args[1], '='))
	{ // export with key, without value
		if (!fuck_only_key(mini_env, cmd_args))
			return (-1);

		// printf("cmd_argher: %c\n", cmd_args[1][i]);
		// new_key = ft_strdup(cmd_args[1]);
		// new_env_var = find_env_var(new_key, mini_env);
		// printf(GREEN"there is != sign\n"RS);
		// if (new_env_var)
		// {
		// 	// If environment variable already exists, set its value to empty string
		// 	// free(new_env_var->value);
		// 	// new_env_var->value = ft_strdup("");//ft_strdup("");
		// 	return (0);
		// }
		// else
		// {
		// 	// If environment variable does not exist, create a new one with empty value
		// 	new_value = NULL; //ft_strdup("");
		// 	new_env_var = create_mini_envvar_node(new_key, new_value, (*mini_env)->content);
		// 	ft_add_envlist(new_env_var, mini_env);

		// }
		// i++;
		// mini_env = &(*mini_env)->next;
		printf(R"print all cmd_args and return new prompt\n"RS);
	}
    return (0);
}

