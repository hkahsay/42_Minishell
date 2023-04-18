#include"../../headers/minishell.h"

int	ft_unset(char **args, t_envnode **mini_env)
{
	int i;
	char    *res;

	i = 1;
	// (*mini_env)->content = malloc(sizeof(t_envnode) + 1);
	// (*mini_env)->content = ft_strjoin((*mini_env)->key, (*mini_env)->value);
	// printf("my content: %s\n", (*mini_env)->content);
	if (args[i] == NULL)
		return(0);
	while (args[i])
	{
		res = check_if_in_env(*mini_env, args[i]);
		if (res == NULL)
		{
			printf("1\n");
			printf("args[i]1 %s\n", args[i]);
			// return (0);
			remove_from_list(*mini_env, args[i]);
		}
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
		printf("4\n");
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
		printf("are we here\n");
		curr = *head;
		(*head) = (*head)->next;
		printf("curr->next->key------ %s\n", curr->next->key);
		printf("head------ %s\n", (*head)->key);

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
	// int		i;
	int		l;

	curr = mini_env;
	l = ft_strlen(arg);
	// i = 0;
	while (curr)
	{
		if (ft_strncmp(curr->key, arg, l + 1) == 0)
			return (curr->key);
		curr = curr->prev;
	}
	return (NULL);
}

// int ft_unset(char **args, t_envnode **env_var)
// {
//     (void)args;
//     (void)env_var;
//     printf("ft_unset\n");
//     return 0;
// }

// int	ft_unset(t_cmd *cmd, t_envnode *env_var)
// {
// 	char	*var_name;
// 	t_envnode	*env_list;
// 	int	len;
// 	int	i;

// 	var_name = cmd->cmd_args->args;
// 	env_list->key = find_env_key(env_var, var_name);
// 	i = 0;
// 	len = ft_strlen(var_name);
// 	while (i < len && env_list == var_name)
// 	{
// 		/* code */
// 	}

// }
