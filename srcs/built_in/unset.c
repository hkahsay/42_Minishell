#include"../../headers/minishell.h"

int	ft_unset(char **args, t_envnode **mini_env)
{
	int i;
	char    *res;

	i = 1;
	if (args[i] == NULL)
		return(0);
	while (args[i])
	{
		res = check_if_in_env(*mini_env, args[i]);
		if (res == NULL)
			remove_from_list(*mini_env, args[i]);
		i++;
	}
	return (0);
}


void	remove_from_list(t_envnode *mini_env, char *key)
{
	t_envnode   *curr;
	t_envnode   *temp;
	int     len;

	curr = mini_env;
	len = ft_strlen((key) + 1);
	if (delete_first_node(&mini_env, curr, key))
		return;
	// printf("curr->content%s\n", curr->key);
	while (curr && ft_strncmp(curr->key, key, len + 1))
	{
		temp = curr;
		curr = curr->next;
		// printf("temp%s\n", temp->key);
	}
	// if((curr->key = NULL))
	//     return ;
	if( curr && !ft_strncmp(curr->key, key, len + 1))
	{
		temp->next = curr->next;
		free (curr->key);
		free (curr->value);
		curr->key = NULL;
		curr->value = NULL;
		free (curr);
		curr = NULL;
	}
	else
		return;
}

int	delete_first_node(t_envnode **head, t_envnode *curr, char *key)
{
	if (head == NULL || *head == NULL)
	{
		printf("env is empty. Cannot remove node.\n");
		return(0);
	}
	if (ft_strcmp(curr->key, key) == 0)
	{
		curr = *head;
		(*head) = (*head)->next;
		// printf("curr->next->key------ %s\n", curr->next->key);
		// printf("head------ %s\n", (*head)->key);

		// free(curr->key);
		// free(curr->value);
		// free(curr);
		// printf("3\n");
		return(1);
	}
	return(0);
}

char	*check_if_in_env(t_envnode *mini_env, char *arg)
{
	t_envnode	*curr;
	int		l;

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
