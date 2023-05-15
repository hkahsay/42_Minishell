#include"../../headers/minishell.h"

static char	*create_content(char *content, t_envnode *my_node)
{
	my_node->content = ft_strdup(content);
	if (!my_node->content)
	{
		my_free(my_node);
		return (NULL);
	}
	return (my_node->content);
}

static char	*create_value(char *value, t_envnode *my_node)
{
	if (value == NULL)
		return (NULL);
	my_node->value = ft_strdup(value);
	if (!my_node->value)
	{
		my_free(my_node->value);
		my_free(my_node);
		return (NULL);
	}
	return (my_node->value);
}

static t_envnode	*create_envnode(char *key, char *value, char *content)
{
	t_envnode	*my_node;

	// printf("ENV 1\n");
	my_node = NULL;
	// printf("ENV 2\n");
	my_node = my_malloc(sizeof(t_envnode) * 1);
	// printf("ENV 3\n");
	if (!my_node)
		return (NULL);
	// printf("ENV 4\n");
	my_node->key = ft_strdup(key);
	// printf("ENV 5\n");
	if (!my_node->key)
	{
		// printf("ENV 6\n");
		my_free(my_node);
		// printf("ENV 7\n");
		return (NULL);
	}
	// printf("ENV 8\n");
	my_node->content = create_content(content, my_node);
	// printf("ENV 9\n");
	if (!my_node->content)
	{
		// printf("ENV 10\n");
		my_free(my_node);
		// printf("ENV 11\n");
		return (NULL);
	}
	// printf("ENV 12\n");
	my_node->value = create_value(value, my_node);
	// printf("ENV 13\n");
	if (!my_node->value)
	{
		// printf("ENV 14\n");
		my_free(my_node);
		// printf("ENV 15\n");
		return (NULL);
	}
	// printf("ENV 16\n");
	return (my_node);
}

t_envnode	*create_mini_envvar_node(char *key, char *value, char *content)
{
	t_envnode	*my_node;

	// printf("ENV 1\n");
	my_node = create_envnode(key, value, content);
	// printf("ENV 2\n");
	if (!my_node)
		return (NULL);
	my_node->prev = NULL;
	my_node->next = NULL;
	return (my_node);
}
