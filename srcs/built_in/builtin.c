#include"../../headers/minishell.h"

int is_builtin(char **cmd, t_envnode *env_var)
{
	t_builtin builtin_cmds[] = {
		{"pwd", &ft_pwd}, //PWD
		{"PWD", &ft_pwd},
		{"cd", &ft_cd}, //CD
		{"CD", &ft_cd},
		{"echo", &ft_echo}, //ECHO
		{"ECHO", &ft_echo},
		{"unset", &ft_unset},
		{"export", &ft_export},
		{"env", &ft_env}, //ENV
		{"ENV", &ft_env},
		{"exit", &ft_exit},
		{NULL, NULL}
	};
	size_t i = 0;
	if (ft_bool_strcspn(cmd[0], "><"))
	{
		printf("found red\n");
		return (-1);
	}
	while (builtin_cmds[i].name != NULL && i < sizeof(builtin_cmds) / sizeof(t_builtin))
	{
		// printf("1. s[%zu] %s\n", i, builtin_cmds[i].name);
		// printf("1. cmd[0][%zu] %s\n", i, cmd[0]);
		// printf("1\n");
		if (strcmp(builtin_cmds[i].name, cmd[0]) == 0)
		{
			// printf("2\n");
			return (builtin_cmds[i].func(cmd, &env_var));
		}
		i++;
	}
	// printf("3. not builtin %s\n", cmd[0]);
	return (-1);
}
