#include "../../headers/minishell.h"

void execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;

	printf(GGREEN "EXECUTE: printing cmd_list\n" RS);
	print_cmd_list(cmd);
	ppline = build_ppline_array(&cmd, cmd_num, mini_env);

	printf(ORS "EXECUTE: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);
	printf(ORS "EXECUTE: ppline->ppline_cmd[0] %s\n" RS, ppline->ppline_cmd[0]);
	printf(ORS "EXECUTE: ppline->ppline_cmd[1] %s\n\n" RS, ppline->ppline_cmd[1]);

	//cmd + D is not working, after 2 times yes

	signal(SIGINT, sig_quit_handler);
	signal(SIGQUIT, sig_quit_handler);
	if (ppline->ppline_idx == 1 && ppline->pp_red_status == 0 && check_if_builtin(ppline->pp_first_cmd) == 0)
	{
		printf(R "EXECUTE: execute_single_builtin\n" RS);
		ppline->pp_exit = execute_builtin(&ppline); //have to be assured, if...
		g_exit_status = ppline->pp_exit;
		printf(LB "\ng_exit_status: %d\n" RS, g_exit_status);
		return ;
	}
	else
		ppline->pp_exit = execute_multi_cmd(ppline);
}
