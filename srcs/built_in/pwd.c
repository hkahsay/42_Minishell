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

int	ft_pwd(t_ppl **ppl)
{
	t_envnode	*curr_var;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	curr_var = (*ppl)->pp_list_env;
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

	// printf("ENV 0\n");
	if (!(*mini_env))
		return (NULL);
	// printf("ENV 1\n");
	node = create_mini_envvar_node((*mini_env)->key, (*mini_env)->value,
			(*mini_env)->content);
			// printf("ENV 2\n");
	if (!node)
		return (NULL);
		// printf("ENV 3\n");
	node->prev = prev;
	// printf("ENV 4\n");
	if ((*mini_env)->next)
	{
		// printf("ENV 5\n");
		node->next = envdup(node, &(*mini_env)->next);
		// printf("ENV 6\n");
		if (!node->next)
		{
			// printf("ENV 7\n");
			while (node->prev)
			{
				// printf("ENV 8\n");
				node = node->prev;
				// printf("ENV 9\n");
			}
			// printf("ENV 10\n");
			return (NULL);
		}
		// printf("ENV 11\n");
	}
	// printf("ENV 12\n");
	return (node);
}

t_envnode	*export_no_cmd(t_envnode **mini_env)
{
	return (envdup(NULL, mini_env));
}
