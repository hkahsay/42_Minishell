#include "../../headers/minishell.h"

int execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;
	// char		*cmd_path;
	// char		**mini_env_arr;

	// cmd_path = NULL;
	printf(R "EXECUTE: printing cmd_list\n" RS);
	print_cmd_list(cmd);
	// mini_env_arr = ft_mini_env_array(mini_env, ft_mini_env_size(mini_env));
	ppline = build_ppline_array(&cmd, cmd_num, mini_env);
	printf(ORS "EXECUTE: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);
	printf(ORS "EXECUTE: ppline->ppline_cmd[0] %s\n" RS, ppline->ppline_cmd[0]);
	printf(ORS "EXECUTE: ppline->ppline_cmd[1] %s\n\n" RS, ppline->ppline_cmd[1]);
	if (ppline && ppline->ppline_cmd)
	{
		if (ppline->ppline_idx == 1) //&& !ppline->ppline_cmd[1])
			ppline->pp_exit = execute_single_cmd(ppline); //, mini_env_arr, &cmd_path
		else
			ppline->pp_exit = execute_multi_cmd(ppline); //, mini_env_arr //return (execute_cmd(mini, &cmd, mini_env));
	}
	// printf(R "ppline->pp_exit: %d\n" RS, ppline->pp_exit);
	g_exit_status = ppline->pp_exit;
	return (0);
}

	// if (ppline->pp_first_cmd && ppline->ppline_idx == 1 && ppline->pp_red_status == 0) //&& !ppline->ppline_cmd[1])
	// {
	// 	if (is_builtin(&ppline->ppline_cmd[0], mini_env) == -1) //ppline->ppline_env
	// 	{
	// 		printf("NOT builtin\n");
	// 		if (!(search_path(ppline, mini_env_arr, &cmd_path)))
	// 		{
	// 			printf("NO PATH\n");
	// 			return (-1);
	// 		}
	// 		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
	// 		// execute_one_cmd(ppline, mini_env_arr, &cmd_path);
	// 		execute_cmd(ppline, mini_env_arr); //return (execute_cmd(mini, &cmd, mini_env));
	// 	}
	// 	return (0);
	// }