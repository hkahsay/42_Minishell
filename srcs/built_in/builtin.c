#include"../../headers/minishell.h"
// t_builtin	builtin_cmds[11];

// 	builtin_cmds[11] = \
// 	{
// 	{"pwd", &ft_pwd}, //PWD
// 	{"PWD", &ft_pwd},
// 	{"cd", &ft_cd}, //CD
// 	{"echo", &ft_echo}, //ECHO
// 	{"ECHO", &ft_echo},
// 	{"unset", &ft_unset},
// 	{"export", &ft_export},
// 	{"env", &ft_env}, //ENV
// 	{"ENV", &ft_env},
// 	{"exit", &ft_exit},
// 	{NULL, NULL}
// 	};

int	check_if_builtin(char *first_cmd)
{
	size_t		i;
	t_builtin	builtin_cmds[11];

	builtin_cmds[0] = (t_builtin){"pwd", &ft_pwd};
	builtin_cmds[1] = (t_builtin){"PWD", &ft_pwd};
	builtin_cmds[2] = (t_builtin){"cd", &ft_cd};
	builtin_cmds[3] = (t_builtin){"echo", &ft_echo};
	builtin_cmds[4] = (t_builtin){"ECHO", &ft_echo};
	builtin_cmds[5] = (t_builtin){"unset", &ft_unset};
	builtin_cmds[6] = (t_builtin){"export", &ft_export};
	builtin_cmds[7] = (t_builtin){"env", &ft_env};
	builtin_cmds[8] = (t_builtin){"ENV", &ft_env};
	builtin_cmds[9] = (t_builtin){"exit", &ft_exit};
	builtin_cmds[10] = (t_builtin){NULL, NULL};
	i = 0;
	while (builtin_cmds[i].name != NULL)
	{
		if (strcmp(builtin_cmds[i].name, first_cmd) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	execute_builtin(t_ppl **ppl)
{
	size_t		i;
	t_builtin	builtin_cmds[11];

	builtin_cmds[0] = (t_builtin){"pwd", &ft_pwd};
	builtin_cmds[1] = (t_builtin){"PWD", &ft_pwd};
	builtin_cmds[2] = (t_builtin){"cd", &ft_cd};
	builtin_cmds[3] = (t_builtin){"echo", &ft_echo};
	builtin_cmds[4] = (t_builtin){"ECHO", &ft_echo};
	builtin_cmds[5] = (t_builtin){"unset", &ft_unset};
	builtin_cmds[6] = (t_builtin){"export", &ft_export};
	builtin_cmds[7] = (t_builtin){"env", &ft_env};
	builtin_cmds[8] = (t_builtin){"ENV", &ft_env};
	builtin_cmds[9] = (t_builtin){"exit", &ft_exit};
	builtin_cmds[10] = (t_builtin){NULL, NULL};
	i = 0;
	while (builtin_cmds[i].name != NULL && i < \
	sizeof(builtin_cmds) / sizeof(t_builtin))
	{
		if (strcmp(builtin_cmds[i].name, (*ppl)->pp_first_cmd) == 0)
			return (builtin_cmds[i].func(ppl));
		i++;
	}
	return (EXIT_FAILURE);
}
