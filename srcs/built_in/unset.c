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
		if (res != NULL)
		{
			if (!remove_from_list(&(*ppl)->pp_list_env, (*ppl)->ppl_cmd[i]))
				ft_exit(ppl);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int remove_from_list(t_envnode **mini_env, char *key)
{
	t_envnode *curr = *mini_env;
	t_envnode *temp;
	int len = ft_strlen(key);

	if (delete_first_node(&mini_env, key))
	{
		return (!!*mini_env);
	}
	while (curr && ft_strncmp(curr->key, key, len + 1))
	{
		temp = curr;
		curr = curr->next;
	}
	if (curr && !ft_strncmp(curr->key, key, len + 1))
	{
		temp->next = curr->next;
		my_free(curr->key);
		my_free(curr->value);
		my_free(curr);
	}
	return (1);
}


int delete_first_node(t_envnode ***hd, char *key)
{
	t_envnode *head = **hd;
	if (head == NULL)
	{
		return (0);
	}
	if (ft_strcmp(head->key, key) == 0)
	{
		**hd = head->next;
		my_free(head->key);
		my_free(head->value);
		my_free(head);
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
