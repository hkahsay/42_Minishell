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

static int	ft_export_noargs(t_envnode **mini_env, t_envnode *new_env) //, char **cmd_args
{
		// printf(YELLOW"only expo\n"RS);
		new_env = export_no_cmd(mini_env);
		if (!new_env)
		{
			printf(YELLOW"new_env\n"RS);
			return (-1);
		}
		printf("content beginning: %s\n", (new_env)->content);
		ft_envnode_sort(&new_env);
		printf(YELLOW"only expo\n"RS);
		print_ex_sorted_envp(new_env); //, cmd_args
		// print_mini_envp(new_env);
		return (0);
}

static int export_key_value(t_envnode **mini_env, char **cmd_args)
{
	char	*new_key;
	char	*new_value;
	// char	*new_content;
	int		i;
	int j;
	// int k = 0;
	// t_envnode *new_env_var = NULL;
	i = 0;
	char	*new_content = *cmd_args;
	printf(R "new_content %s\n" RS, new_content);
	// while (cmd_args[1][k])
	// {
	// 	k++;
	// }
	// new_content = ft_substr((char *)cmd_args[1], 0, k);
	while (new_content[i] != '=')
	{
		printf(BLUE "new_content %s\n"RS, new_content);
		printf(R"there is == sign in key\n"RS);
		i++;
	}
	new_key = ft_substr(new_content, 0, i);
	i++;
	j = 0;
	while (new_content[j] != '\0')
	{
		printf(GREEN"*cmd_args[1] %s\n"RS, new_content);
		printf(OR"there is == sign in value\n"RS);
		j++;
	}
	new_value = ft_substr(new_content, i, j);
	if (!ft_setenv(new_key, new_value, new_content, mini_env))
		return (-1);
	return (0);
}

static int export_key(t_envnode **mini_env, char **cmd_args)
{
	char	*new_key;
	char	*new_value;
	int		i;
	t_envnode *new_env_var;
	char	*new_content;

	i = 0;
	new_env_var = NULL;
	new_content = *cmd_args;
	// printf("cmd_argher: %s\n", *cmd_args);
	new_key = ft_strdup(new_content);
	new_env_var = find_env_var(new_key, mini_env);
	// printf(GREEN"there is != sign\n"RS);
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
	int	k = 1;
	if (cmd_args[1] == NULL && mini_env)
	{ // export
		if (!ft_export_noargs(mini_env, new_env_var)) //&cmd_args[k], 
			return (-1);
		return (0);	
	}
	while (cmd_args[k])
	{
		if (cmd_args[k] && ft_strchr(cmd_args[k], '=')) //ft_strchr(const char	*s, int c)
		{ // export with key and value
			if (!export_key_value(mini_env, &cmd_args[k]))
				return (-1);
		}
		if (cmd_args[k] && !ft_strchr(cmd_args[k], '='))
		{ // export with key, without value
			if (!export_key(mini_env, &cmd_args[k]))
				return (-1);

			// printf(R"print all cmd_args and return new prompt\n"RS);
		}
		k++;
	}
	
    return (0);
}

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
