#include "../../headers/minishell.h"

void execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;

	ppline = build_ppline_array(&cmd, cmd_num, mini_env);
	if (!ppline)
		return ;
	ter_attr_handler_off();
	signals_default();
	if (ppline->ppline_idx == 1 && ppline->pp_red_status == 0 && check_if_builtin(ppline->pp_first_cmd) == 0)
	{
		if (execute_to_builtin(ppline))
			msg_error("error executing builtin: ", errno);
	}
	else
	{
		if (execute_multi_cmd(ppline))
			msg_error("error executing multi_cmd: ", errno);
	}
	signal_at_beginning();
	ter_attr_handler_on();
}
