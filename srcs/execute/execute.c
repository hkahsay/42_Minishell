#include "../../headers/minishell.h"

// g_mini.exit_status;

void	execute_cmd(t_ppline *ppline, char **mini_env_array, char **cmd_path)
{
	// printf(GREEN "execution\n" RS);
	if (execve(*cmd_path, ppline->ppline_cmd, mini_env_array) == -1)
		msg_error(ft_strjoin(ppline->ppline_cmd[0], " : command not found\n"), 127);
	// return (0);
}

int execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;
	char		*cmd_path;
	char		**mini_env_arr;

	cmd_path = NULL;
	printf(R "EXECUTE: printing cmd_list\n" RS);
	print_cmd_list(cmd);
	mini_env_arr = ft_mini_env_array(mini_env, ft_mini_env_size(mini_env));
	ppline = build_ppline_array(&cmd, cmd_num, mini_env_arr);
	printf(ORS "EXECUTE: ppline->ppline_cmd[0] %s\n" RS, ppline->ppline_cmd[0]);
	if (is_builtin(&ppline->ppline_cmd[0], mini_env) == -1) //ppline->ppline_env
	{
		printf("NOT builtin\n");
		if (!(search_path(ppline, mini_env_arr, &cmd_path)))
		{
			printf("NO PATH\n");
			return (-1);
		}
		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
		execute_cmd(ppline, mini_env_arr, &cmd_path);
	}
	return (0); //return (execute_cmd(mini, &cmd, mini_env));
}
