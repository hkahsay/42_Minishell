#include "../../headers/minishell.h"

void print_mini_envp(t_envnode *temp)
{
	int i = 0;

	while (temp)
	{
		printf("LIST: %s=%s\n", temp->key, temp->value);
		temp = temp->next;
		i++;
	}
	printf("%d\n", i);
}


void free_mini_envp(t_envnode *head)
{
	t_envnode *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

t_envnode *create_mini_envvar_node(char *key, char *value) //, int i
{
	t_envnode *my_node = NULL;

	my_node = malloc(sizeof(t_envnode) * 1);
	if (!my_node)
		return (NULL);
	my_node->key = ft_strdup(key);
	if (!my_node->key)
	{
		free(my_node);
		return (NULL);
	}
	my_node->value = ft_strdup(value);
	if (!my_node->value)
	{
		free(my_node->key);
		free(my_node);
		return (NULL);
	}
	my_node->prev = NULL;
	my_node->next = NULL;
	// printf("nodes %d OK %s = %s\n", i, my_node->key, my_node->value);
	return (my_node);
}

t_envnode *dublicate_env(char **envp) // fnct returns a starting address of the linked list env
{
	// char **envp_var;
	char *key;
	char *value;
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
		// printf("%s\n", value);
		// envp_var = ft_split(envp[i], '=');
		// key = ft_strdup(envp_var[0]);
		// value = ft_strdup(envp_var[1]);
		// printf("%d %s %s\n", (envp_lines + 1), key, value);
		node = create_mini_envvar_node(key, value); //, i
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
