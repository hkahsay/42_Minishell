#include "../../headers/minishell.h"

void	free_mini_envp(t_envnode *head)
{
	t_envnode	*temp;

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

char	*get_env_key(char *env_var)
{
	int		i;
	char	*key;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	key = ft_substr(env_var, 0, i);
	if (!key)
		return (NULL);
	return (key);
}

char	*get_env_value(char *env_var)
{
	int		i;
	char	*value;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	if (!env_var[i])
		return (NULL);
	value = ft_strdup(env_var + i + 1);
	if (!value)
		return (NULL);
	return (value);
}
