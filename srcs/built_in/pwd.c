#include"../../headers/minishell.h"

int ft_pwd(t_ppline **ppline) //char **args, t_envnode **mini_env
{
	t_envnode	*curr_var;
	char		*cwd;
	// t_envnode	*env_var;

	// env_var = NULL;
	cwd = getcwd(NULL, 0);
	curr_var = (*ppline)->pp_list_env;
	// if ((*ppline)->ppline_cmd[1])
	// {
	// 	printf("too many arguments\n");
	// 	exit(0);
	// }
	while(curr_var != 0)//&& (*ppline)->ppline_cmd[1] == 0
	{
		// printf("b %s\n", curr_var->value);
		if (ft_strcmp(curr_var->key, "pwd") == 0 || ft_strcmp(curr_var->key, "PWD") == 0)
		{
			if(ft_strcmp(curr_var->value, cwd) == 0)
			{
				printf("%s\n", curr_var->value);
				free(cwd);
				return (EXIT_SUCCESS);
			}
			else
			{
				my_free(curr_var->value);
				curr_var->value = ft_strdup(cwd);
				printf("curr_var->value %s\n", curr_var->value);
				free(cwd); //TODO: FREE
				return(0);
			}
		}
		curr_var = curr_var->next;
	}
	free(cwd);
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
