#include "../../headers/minishell.h"

void free_mini_envp(t_envnode *head)
{
	t_envnode *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp->content);
		free(temp);
	}
}

// t_envnode *create_mini_envvar_node(char *key, char *value, char *content)//, int i
// {
// 	t_envnode *my_node = NULL;

// 	my_node = malloc(sizeof(t_envnode) * 1);
// 	if (!my_node)
// 		return (NULL);
// 	// printf("&new_env_var %p\n", new_env_var);
// 	my_node->key = ft_strdup(key);
// 	if (!my_node->key)
// 	{
// 		// free(my_node);
// 		return (NULL);
// 	}
// 	if (my_node->content == NULL)
// 		my_node->content = NULL;
// 	else
// 	{
// 		my_node->content = ft_strdup(content);
// 		if (!my_node->content)
// 		{
// 			// free(my_node);
// 			return (NULL);
// 		}
// 	}
// 	// printf("value in sorting %s\n", value);
// 	if (value == NULL)
// 	{
// 		printf("OK\n");
// 		my_node->value = NULL;
// 	}
// 	else
// 		my_node->value = ft_strdup(value);
// 	// printf("nodes OK %s = %s\n", my_node->key, my_node->value);
// 	if (!my_node->value)
// 	{
// 		// free(my_node->key);
// 		// free(my_node);
// 		return (NULL);
// 	}
// 	my_node->prev = NULL;
// 	my_node->next = NULL;
// 	// printf("nodes OK %s = %s\n", my_node->key, my_node->value);
// 	return (my_node);
// }

t_envnode *create_fuck(char *key)//, int i
{
	t_envnode *my_node = NULL;

	my_node = malloc(sizeof(t_envnode) * 1);
	if (!my_node)
		return (NULL);
	// printf("&new_env_var %p\n", new_env_var);
	my_node->key = ft_strdup(key);
	my_node->value = NULL;
	my_node->content = ft_strdup(key);
	if (!my_node->key)
	{
		// free(my_node);
		return (NULL);
	}
	// if (my_node->content == NULL)
	// 	my_node->content = NULL;
	// else
	// {
	// 	my_node->content = ft_strdup(content);
	// 	if (!my_node->content)
	// 	{
	// 		// free(my_node);
	// 		return (NULL);
	// 	}
	// }
	// printf("value in sorting %s\n", value);
	// if (value == NULL)
	// {
	// 	my_node->value = NULL;
	// printf("OK\n");
	// }
	// else
	// 	my_node->value = ft_strdup(value);
	// printf("nodes OK %s = %s\n", my_node->key, my_node->value);
	// if (!my_node->value)
	// {
	// 	// free(my_node->key);
	// 	// free(my_node);
	// 	return (NULL);
	// }
	my_node->prev = NULL;
	my_node->next = NULL;
	printf("nodes OK %s = %s\n", my_node->key, my_node->value);
	return (my_node);
}

t_envnode *duplicate_env(char **envp) // fnct returns a starting address of the linked list env
{
	// char **envp_var;
	char *key;
	char *value;
	char *content;
	t_envnode *node = NULL;
	t_envnode *head = NULL;
	t_envnode *temp = NULL;
	
	int i = 0;
	int j = 0;
	//hello from Nicole
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		// printf("j avant '=': %d\n", j);
		key = ft_substr(envp[i], 0, j);
		// printf("%s\n", key);
		value = ft_substr(envp[i], (j + 1), ft_strlen(envp[i]));
		content = ft_strdup(envp[i]);
		printf("from mini_env %s\n", value);
		// envp_var = ft_split(envp[i], '=');
		// key = ft_strdup(envp_var[0]);
		// value = ft_strdup(envp_var[1]);
		// printf("%d %s %s\n", (envp_lines + 1), key, value);
		node = create_mini_envvar_node(key, value, content);
		// printf("Node %d OK\n", i);
		// usleep(100000000);
		if (!node)
			return (NULL);
		if (head == NULL)
			head = node;
		else
		{
			temp = head;
			while (temp->next)
				temp = temp->next;
			temp->next = node;
			node->prev = temp;
			temp = node;
		}
		// free(key);
		// free(value);
		i++;
	}
	// printf("envp[i] i: %d\n", i);
	return (head);
}
