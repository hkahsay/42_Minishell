#include"../../headers/minishell.h"

int	check_if_builtin(char *first_cmd)
{
	t_builtin builtin_cmds[] = {
		{"pwd", &ft_pwd}, //PWD
		{"PWD", &ft_pwd},
		{"cd", &ft_cd}, //CD
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
	while (builtin_cmds[i].name != NULL)
	{
		if (strcmp(builtin_cmds[i].name, first_cmd) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int execute_builtin(t_ppline **ppline)
{
	t_builtin builtin_cmds[] = {
		{"pwd", &ft_pwd}, //PWD
		{"PWD", &ft_pwd},
		{"cd", &ft_cd}, //CD
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
	while (builtin_cmds[i].name != NULL && i < sizeof(builtin_cmds) / sizeof(t_builtin))
	{
		if (strcmp(builtin_cmds[i].name, (*ppline)->pp_first_cmd) == 0)

			return (builtin_cmds[i].func(ppline));
		i++;
	}
	return (EXIT_FAILURE);
}
