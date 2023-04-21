#include "../../headers/minishell.h"

int	ft_mini_env_size(t_envnode *mini_env_head)
{
	t_envnode *mini_temp;
	int		size;

	mini_temp = mini_env_head;
	size = 0;
	while (mini_temp != NULL)
	{
		if (mini_temp != NULL)
			size++;
		mini_temp = mini_temp->next;
	}
	return (size);
}

char	**ft_mini_env_array(t_envnode *mini_env, int size)
{
	char	**mini_env_array;
	int		i;

	i = 0;
	mini_env_array = (char **)my_malloc(sizeof(char *) * (size + 1));
	mini_env_array[size] = NULL;
	while (mini_env && mini_env_array[i] && i < size)
	{
		mini_env_array[i] = mini_env->content;
		i++;
		mini_env = mini_env->next;
	}
	return (mini_env_array);
}