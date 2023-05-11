#include "../../headers/minishell.h"

t_envnode	*init_envnode(void)
{
	t_envnode	*env_node;

	env_node = ft_calloc(1, sizeof(t_envnode));
	if (!env_node)
	{
		ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
		msg_error("minishell_VH: error memory", errno);
	}
	return (env_node);
}
