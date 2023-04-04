#include"../../headers/minishell.h"

int	ft_unset(t_cmd *cmd, t_envnode *env_var)
{
	char	*var_name;
	t_envnode	*env_list;
	int	len;
	int	i;

	var_name = cmd->cmd_args->args;
	env_list->key = find_env_var(env_var, var_name);
	i = 0;
	len = ft_strlen(var_name);
	while (i < len && env_list == var_name)
	{
		/* code */
	}
	
}