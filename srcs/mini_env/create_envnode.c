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

	my_node = NULL;
	my_node = my_malloc(sizeof(t_envnode) * 1);
	if (!my_node)
		return (NULL);
	my_node->key = ft_strdup(key);
	if (!my_node->key)
	{
		my_free(my_node);
		return (NULL);
	}
	my_node->content = create_content(content, my_node);
	if (!my_node->content)
	{
		my_free(my_node);
		return (NULL);
	}
	my_node->value = create_value(value, my_node);
	if (!my_node->value)
	{
		my_free(my_node);
		return (NULL);
	}
	return (my_node);
}

t_envnode	*create_mini_envvar_node(char *key, char *value, char *content)
{
	t_envnode	*my_node;

	my_node = create_envnode(key, value, content);
	if (!my_node)
		return (NULL);
	my_node->prev = NULL;
	my_node->next = NULL;
	return (my_node);
}

// t_envnode	*create_mini_envvar_node(char *key, char *value, char *content)
// {
// 	t_envnode	*my_node;

// 	my_node = NULL;
// 	my_node = my_malloc(sizeof(t_envnode) * 1);
// 	if (!my_node)
// 		return (NULL);
// 	my_node->key = ft_strdup(key);
// 	if (!my_node->key)
// 	{
// 		my_free(my_node);
// 		return (NULL);
// 	}
// 	my_node->content = ft_strdup(content);
// 	if (!my_node->content)
// 	{
// 		my_free(my_node->content);
// 		my_free(my_node);
// 		return (NULL);
// 	}
// 	if (value == NULL)
// 		my_node->value = NULL;
// 	else
// 		my_node->value = ft_strdup(value);
// 	if (!my_node->value)
// 	{
// 		my_free(my_node->value);
// 		my_free(my_node);
// 		return (NULL);
// 	}
// 	my_node->prev = NULL;
// 	my_node->next = NULL;
// 	return (my_node);
// }
