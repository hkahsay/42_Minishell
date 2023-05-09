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
	// printf(LIME "ft_mini_env_array\n" RS);
	char	**mini_env_array;
	int		i;
	t_envnode	*cur = mini_env;

	i = 0;
	// printf(LIME "mini_envp_envnode\n" RS);
	// print_mini_envp(cur);
	mini_env_array = (char **)my_malloc(sizeof(char *) * (size + 1));
	if (!mini_env_array)
		return (NULL);
	mini_env_array[size] = NULL;
	// printf("i: %d\n", i);
	// printf("size: %d\n", size);
	while (cur && i < size) //  && i < size //mini_env_array[i] && 
	{
		mini_env_array[i] = cur->content;
		// printf(LIME "mini_env_array[%d] %s\n" RS, i, mini_env_array[i]);
		i++;
		cur = cur->next;
	}
	// printf("i: %d\n", i);
	// printf(LIME "mini_env_array\n" RS);
	// print_mini_env_array(mini_env_array);
	// my_free(mini_env_array);
	return (mini_env_array);
}
