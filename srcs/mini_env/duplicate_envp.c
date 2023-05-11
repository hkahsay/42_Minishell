#include "../../headers/minishell.h"

static void	free_env_node(char *key, char *value, char *content)
{
	my_free(key);
	my_free(value);
	my_free(content);
}

static t_envnode	*create_envvar_node(char *env_var)
{
	char		*key;
	char		*value;
	char		*content;
	t_envnode	*node;

	key = get_env_key(env_var);
	if (!key)
		return (NULL);
	value = get_env_value(env_var);
	content = ft_strdup(env_var);
	if (!content)
	{
		my_free(key);
		my_free(value);
		return (NULL);
	}
	node = create_mini_envvar_node(key, value, content);
	if (!node)
	{
		free_env_node(key, value, content);
		return (NULL);
	}
	free_env_node(key, value, content);
	return (node);
}

static void	add_envnode_to_end(t_envnode **head, t_envnode *node)
{
	t_envnode	*temp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
	node->prev = temp;
	temp = node;
}

t_envnode	*duplicate_env(char **envp)
{
	t_envnode	*head;
	t_envnode	*node;
	int			i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_envvar_node(envp[i]);
		if (!node)
			return (NULL);
		add_envnode_to_end(&head, node);
		i++;
	}
	return (head);
}

// t_envnode	*duplicate_env(char **envp)
// {
// 	char		*key;
// 	char		*value;
// 	char		*content;
// 	t_envnode	*node;
// 	t_envnode	*head;
// 	t_envnode	*temp;
// 	int			i;
// 	int			j;

// 	node = NULL;
// 	head = NULL;
// 	temp = NULL;
// 	i = 0;
// 	j = 0;
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (envp[i][j] != '=')
// 			j++;
// 		key = ft_substr(envp[i], 0, j);
// 		value = ft_substr(envp[i], (j + 1), ft_strlen(envp[i]));
// 		content = ft_strdup(envp[i]);
// 		node = create_mini_envvar_node(key, value, content);
// 		if (!node)
// 			return (NULL);
// 		if (head == NULL)
// 			head = node;
// 		else
// 		{
// 			temp = head;
// 			while (temp->next)
// 				temp = temp->next;
// 			temp->next = node;
// 			node->prev = temp;
// 			temp = node;
// 		}
// 		my_free(key);
// 		my_free(value);
// 		my_free(content);
// 		i++;
// 	}
// 	return (head);
// }
