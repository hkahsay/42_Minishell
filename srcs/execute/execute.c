#include "../../headers/minishell.h"

void	execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppl	*ppl;

	ppl = build_ppl(&cmd, cmd_num, mini_env);
	if (ppl == NULL)
		return ;
	my_free(cmd);
	ter_attr_handler_off();
	if (ppl->ppl_idx == 1 && ppl->pp_red_status == 0 && \
	check_if_builtin(ppl->pp_first_cmd) == 0)
	{
		if (execute_to_builtin(ppl))
			msg_error("error executing builtin: ", errno);
	}
	else
	{
		if (execute_pipe_cmd(ppl))
			msg_error("error executing multi_cmd: ", errno);
	}
	signal_at_beginning();
	ter_attr_handler_on();
}
