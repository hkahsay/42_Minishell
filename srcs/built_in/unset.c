#include"../../headers/minishell.h"

int	ft_unset(t_ppl **ppl)
{
	int		i;
	char	*res;

	i = 1;
	if ((*ppl)->ppl_cmd[i] == NULL)
		return (0);
	while ((*ppl)->ppl_cmd[i])
	{
		res = check_if_in_env((*ppl)->pp_list_env, (*ppl)->ppl_cmd[i]);
		if (res == NULL)
			remove_from_list((*ppl)->pp_list_env, (*ppl)->ppl_cmd[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	remove_from_list(t_envnode *mini_env, char *key)
{
	t_envnode	*curr;
	t_envnode	*temp;
	int			len;

	curr = mini_env;
	len = ft_strlen((key) + 1);
	if (delete_first_node(&mini_env, curr, key))
		return ;
	while (curr && ft_strncmp(curr->key, key, len + 1))
	{
		temp = curr;
		curr = curr->next;
	}
	if (curr && !ft_strncmp(curr->key, key, len + 1))
	{
		temp->next = curr->next;
		my_free (curr->key);
		my_free (curr->value);
		curr->key = NULL;
		curr->value = NULL;
		my_free (curr);
		curr = NULL;
	}
	else
		return ;
}

int	delete_first_node(t_envnode **head, t_envnode *curr, char *key)
{
	if (head == NULL || *head == NULL)
	{
		printf("env is empty. Cannot remove node.\n");
		return (0);
	}
	if (ft_strcmp(curr->key, key) == 0)
	{
		printf("are we here\n");
		curr = *head;
		(*head) = (*head)->next;
		printf("curr->next->key------ %s\n", curr->next->key);
		printf("head------ %s\n", (*head)->key);
		return (1);
	}
	return (0);
}

char	*check_if_in_env(t_envnode *mini_env, char *arg)
{
	t_envnode	*curr;
	int			l;

	curr = mini_env;
	l = ft_strlen(arg);
	while (curr)
	{
		if (ft_strncmp(curr->key, arg, l + 1) == 0)
			return (curr->key);
		curr = curr->prev;
	}
	return (NULL);
}
