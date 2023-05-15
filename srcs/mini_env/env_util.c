#include"../../headers/minishell.h"

t_envnode	*find_env_var(char *key, t_envnode **current_dir)
{
	t_envnode	*current;

	current = *current_dir;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	update_env_var(char *key, char *value)
{
	t_envnode	*var;

	var = NULL;
	var = find_env_var(key, &var);
	if (var != NULL)
	{
		my_free(var->value);
		var->value = ft_strdup(value);
	}
}

void	ft_add_envlist(t_envnode *new_node, t_envnode **env)
{
	t_envnode	*curr_node;

	curr_node = *env;
	if (curr_node == NULL)
	{
		*env = new_node;
		return ;
	}
	while (curr_node->next != NULL)
	{
		curr_node = curr_node->next;
	}
	curr_node->next = new_node;
}

static void	swap_envnodes(t_envnode *node1, t_envnode *node2)
{
	t_envnode	temp;

	temp.key = ft_strdup(node1->key);
	temp.value = ft_strdup(node1->value);
	temp.content = ft_strdup(node1->content);
	my_free(node1->content);
	my_free(node1->key);
	my_free(node1->value);
	node1->key = ft_strdup(node2->key);
	node1->value = ft_strdup(node2->value);
	node1->content = ft_strdup(node2->content);
	my_free(node2->content);
	my_free(node2->key);
	my_free(node2->value);
	node2->key = ft_strdup(temp.key);
	node2->value = ft_strdup(temp.value);
	node2->content = ft_strdup(temp.content);
}

void	ft_envnode_sort(t_envnode **mini_env)
{
	int			sorted;
	t_envnode	*current;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = *mini_env;
		while (current && current->next)
		{
			if (ft_strcmp(current->content, current->next->content) > 0)
			{
				swap_envnodes(current, current->next);
				sorted = 0;
			}
			current = current->next;
		}
	}
}
