#include"../../headers/minishell.h"

static int	cmp_pwd(t_envnode *curr_var, char *cwd)
{
	if (ft_strcmp(curr_var->key, "pwd") == 0 \
		|| ft_strcmp(curr_var->key, "PWD") == 0)
	{
		if (ft_strcmp(curr_var->value, cwd) == 0)
		{
			printf("%s\n", curr_var->value);
			free(cwd);
			return (EXIT_SUCCESS);
		}
		else
		{
			my_free(curr_var->value);
			curr_var->value = ft_strdup(cwd);
			printf("%s\n", curr_var->value);
			free(cwd);
			return (0);
		}
	}
	return (0);
}

int	ft_pwd(t_ppline **ppline)
{
	t_envnode	*curr_var;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	curr_var = (*ppline)->pp_list_env;
	while (curr_var != 0)
	{
		cmp_pwd(curr_var, cwd);
		curr_var = curr_var->next;
	}
	return (EXIT_SUCCESS);
}

t_envnode	*envdup(t_envnode *prev, t_envnode **mini_env)
{
	t_envnode	*node;

	if (!(*mini_env))
		return (NULL);
	node = create_mini_envvar_node((*mini_env)->key, (*mini_env)->value,
			(*mini_env)->content);
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
