#include "../../headers/minishell.h"

int	export(char **cmds, t_envnode **mini_env)
{
	char	*var_name;
	char	*var_value;
	int		len;
	int		i;
	int		j;

	//  if (argc < 2) {
    //     printf("Usage: export VAR=value\n");
    //     return 1;
    // }
	cmd[0] = ;

	var_name = strdup(env_var->key);
	var_value = strdup(env_var->value);
	len = ft_strlen(cmd->cmd_wnode->file);
	i = 0;
	j = 0;
	while (i < len && cmd->cmd_wnode->file[i] != '=') //i = 0
	{
		if (ft_strcmp(&cmd->cmd_wnode->file[0], "export") == 0)
			var_name = cmd->cmd_wnode->file[i + 1];
		i++;
	}
	var_name[i] = '\0';
	if (i == len)
	{
		printf("Usage: export VAR=value\n");
		return(1);
	}
	while (i < cmd->cmd_wnode->file[i])
	{
		if (ft_strcmp(&cmd->cmd_wnode->file[0], "export") == 0)
			var_value[j] = cmd->cmd_wnode->file[i];
		i++;
		j++;
	}
	var_value[j] = '\0';
	//-----setenv----
	ft_setenv(var_name, var_value, &env_var);
	printf("%s=%s", var_name, var_value);
	free(var_name);
	free(var_value);
	return (0);
}
