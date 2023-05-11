#include "../../headers/minishell.h"

// t_envnode	*init_envnode(void)
// {
// 	t_envnode *env_node;

// 	env_node = my_malloc(sizeof(t_envnode) * 1);
// 	if (env_node != NULL)
// 		ft_memset(env_node, 0, sizeof(t_envnode));
// 	return (env_node);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr;

// 	ptr = my_malloc(count * size);
// 	if (ptr == NULL)
// 		return (ptr);
// 	ft_bzero(ptr, size * count);
// 	return (ptr);
// }

t_envnode	*init_envnode(void)
{
	t_envnode *env_node;

	env_node = ft_calloc(1, sizeof(t_envnode));
	if (!env_node)
	{
		ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
		msg_error("minishell_VH: error memory", errno);
	}
	return (env_node);
}