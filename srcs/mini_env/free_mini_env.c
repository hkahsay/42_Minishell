#include "../../headers/minishell.h"

void free_mini_envp(t_envnode *head)
{
	t_envnode *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		my_free(temp->key);
		my_free(temp->value);
		my_free(temp->content);
		my_free(temp);
	}
}

t_envnode *duplicate_env(char **envp)
{
	char *key;
	char *value;
	char *content;
	t_envnode *node;
	t_envnode *head;
	t_envnode *temp;
	int i;
	int j;

	node = NULL;
	head = NULL;
	temp = NULL;
	i = 0;
	j = 0;
	//hello from Nicole
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		key = ft_substr(envp[i], 0, j);
		// printf("%s\n", key);
		value = ft_substr(envp[i], (j + 1), ft_strlen(envp[i]));
		content = ft_strdup(envp[i]);
		// printf("from mini_env %s\n", value);
		node = create_mini_envvar_node(key, value, content);
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
		my_free(key);
		my_free(value);
		my_free(content);
		i++;
	}
	// printf("envp[i] i: %d\n", i);
	return (head);
}
