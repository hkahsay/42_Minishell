#include "../../headers/minishell.h"

// int	execute_multi_cmd(t_ppline *ppline) //, char **mini_env_arr
// {
// 	printf(GGREEN "Execution of several cmds\n" RS);
// 	t_ppline	*pp_curr;

// 	pp_curr = ppline;
// 	init_pipe(&ppline);
// 	while (pp_curr)
// 	{
// 		pp_curr->pp_pid = fork();	
// 		if (pp_curr->pp_pid == 0)
// 		{
// 			if (pp_curr->pp_outfile > 2)
// 				dup2(pp_curr->pp_pipe[1], STDOUT_FILENO);
// 			if (pp_curr->pp_infile > 2)
// 				dup2(pp_curr->pp_pipe[0], STDIN_FILENO);
// 			close_pipes(ppline);
// 		}
// 	}
// 	return (0);
// }

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