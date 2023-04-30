#include "../../headers/minishell.h"

void execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;

	print_cmd_list(cmd);
	ppline = build_ppline_array(&cmd, cmd_num, mini_env);

	signal(SIGINT, sig_quit_handler);
	signal(SIGQUIT, sig_quit_handler);
	if (ppline->ppline_idx == 1 && ppline->pp_red_status == 0 && check_if_builtin(ppline->pp_first_cmd) == 0)
	{
		ppline->pp_exit = execute_builtin(&ppline);
		g_exit_status = ppline->pp_exit;
		return ;
	}
	else
		ppline->pp_exit = execute_multi_cmd(ppline);
	wait_execution(&ppline);	
}
