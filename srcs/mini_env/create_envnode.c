#include"../../headers/minishell.h"

t_envnode *create_mini_envvar_node(char *key, char *value, char *content)//, int i
{
	t_envnode *my_node = NULL;

	my_node = malloc(sizeof(t_envnode) * 1);
	if (!my_node)
		return (NULL);
	// printf("&new_env_var %p\n", new_env_var);
	my_node->key = ft_strdup(key);
	if (!my_node->key)
	{
		// free(my_node);
		return (NULL);
	}
	if (my_node->content == NULL)
		my_node->content = NULL;
	else
	{
		my_node->content = ft_strdup(content);
		if (!my_node->content)
		{
			// free(my_node);
			return (NULL);
		}
	}
	// printf("value in sorting %s\n", value);
	if (value == NULL)
	{
		printf("OK\n");
		my_node->value = NULL;
	}
	else
		my_node->value = ft_strdup(value);
	// printf("nodes OK %s = %s\n", my_node->key, my_node->value);
	if (!my_node->value)
	{
		// free(my_node->key);
		// free(my_node);
		return (NULL);
	}
	my_node->prev = NULL;
	my_node->next = NULL;
	// printf("nodes OK %s = %s\n", my_node->key, my_node->value);
	return (my_node);
}

