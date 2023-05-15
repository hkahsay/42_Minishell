#include "../../headers/minishell.h"

void	finish_exec(t_ppl **p_ppl)
{
	t_ppl	*ppl;

	ppl = *p_ppl;
	close_red_fds(&ppl);
	close_fds(&ppl);
}

void	finish_multi_exec(t_ppl **p_ppl)
{
	t_ppl	*ppl;

	ppl = *p_ppl;
	execute_parent(&ppl);
	close(STDOUT_FILENO);
	close_fds(&ppl);
	dup2_saved_stds(&ppl);
	close_saved_stds(&ppl);
}
