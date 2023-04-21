#include"../../headers/minishell.h"

/* Helper function to find an environment variable by key */
t_envnode *find_env_var(char *key, t_envnode **current_dir)
{
	t_envnode *current;

	current = *current_dir;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

void update_env_var(char* key, char* value)
{
	t_envnode *var;

	// if (!key || !value)
	//     return (NULL);
	var = NULL;
	var = find_env_var(key, &var);
	if (var != NULL)
	{
		free(var->value);
		var->value = strdup(value);
	}
}

void ft_add_envlist(t_envnode *new_node, t_envnode **env)
{
	t_envnode *curr_node = *env;

	// printf(R"NEW node %s\n" RS, new_node->key);
	if (curr_node == NULL)
	{
		*env = new_node;
		return;
	}
	while (curr_node->next != NULL)
	{
		curr_node = curr_node->next;
	}
	curr_node->next = new_node;
	// printf(R"NEW node %s\n" RS, new_node->key);
}

void ft_envnode_sort(t_envnode **mini_env)
{
	int sorted;
	t_envnode *current;
	t_envnode  temp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1; // assume the list is sorted initially
		current = *mini_env;
		while (current && current->next)
		{
			if (ft_strcmp(current->content, current->next->content) > 0)
			{
				temp.key = ft_strdup(current->key);
				temp.value = ft_strdup(current->value);
				temp.content = ft_strdup(current->content);
				free(current->content);
				free(current->key);
				free(current->value);
				current->key = ft_strdup(current->next->key);
				current->value = ft_strdup(current->next->value);
				current->content = ft_strdup(current->next->content);
				free(current->next->content);
				free(current->next->key);
				free(current->next->value);
				current->next->key = ft_strdup(temp.key);
				current->next->value = ft_strdup(temp.value);
				current->next->content = ft_strdup(temp.content);
				sorted = 0; // the list is not sorted yet
			}
			current = current->next;
		}
	}
}