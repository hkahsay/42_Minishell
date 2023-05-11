#include "../../headers/minishell.h"

t_envnode	*init_envnode(void)
{
	t_envnode	*env_node;

	env_node = ft_calloc(1, sizeof(t_envnode));
	if (!env_node)
		error_mem();
	return (env_node);
}
