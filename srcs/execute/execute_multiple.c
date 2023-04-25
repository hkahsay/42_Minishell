#include "../../headers/minishell.h"

int	execute_multi_cmd(t_ppline *ppline) //, char **mini_env_arr
{
	// char		*cmd_path;

	// cmd_path = NULL;
	(void)ppline;
	// (void)mini_env_array;
	printf(GGREEN "Execution of several cmds\n" RS);
	// if (ppline->pp_first_cmd && ppline->ppline_idx == 1 && ppline->pp_red_status == 0) //&& !ppline->ppline_cmd[1])
	// {
	// 	// if (is_builtin(&ppline->ppline_cmd[0], mini_env) == -1) //ppline->ppline_env
	// 	// {
	// 	// 	printf("NOT builtin\n");
	// 		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr
	// 		{
	// 			printf("NO PATH\n");
	// 			return (-1);
	// 		}
	// 		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
	// 		// execute_single_cmd(ppline); //, mini_env_arr, &cmd_path
	// 	// }
	// 	return (0);
	// }
	return (0);
}
