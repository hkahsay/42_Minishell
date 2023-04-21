#include"../../headers/minishell.h"

int	ft_builtin(char *first_cmd)
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
	size_t i;

	i = 0;
	if (strcmp(builtin_cmds[i].name, first_cmd) == 0)
	{
		// printf("2\n");
		return (1);
	}
	return (0);
}
