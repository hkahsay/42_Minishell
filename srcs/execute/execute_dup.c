#include "../../headers/minishell.h"

void	dup_fds(t_ppl **ppl)
{
	if ((*ppl)->pp_infile != STDIN_FILENO)
		dup2((*ppl)->pp_infile, STDIN_FILENO);
	if ((*ppl)->pp_outfile != STDOUT_FILENO)
		dup2((*ppl)->pp_outfile, STDOUT_FILENO);
	close_fds(ppl);
}

void	dup_red_fds(t_ppl **ppl)
{
	if ((*ppl)->pp_fd_out != STDOUT_FILENO)
		dup2((*ppl)->pp_fd_out, STDOUT_FILENO);
	if ((*ppl)->pp_fd_in != 0)
		dup2((*ppl)->pp_fd_in, STDIN_FILENO);
}

void	dup_saved_stds(t_ppl **ppl)
{
	(*ppl)->saved_stdin = dup(STDIN_FILENO);
	(*ppl)->saved_stdout = dup(STDOUT_FILENO);
}

void	dup2_saved_stds(t_ppl **ppl)
{
	dup2((*ppl)->saved_stdout, STDOUT_FILENO);
	dup2((*ppl)->saved_stdin, STDIN_FILENO);
}

void	*manage_dup(t_ppl **ppl_p)
{
	t_ppl	*ppl;

	ppl = *ppl_p;
	if (ppl->pp_heredoc_status == 0)
		dup_fds(&ppl);
	if (ppl->pp_heredoc_status == 1)
	{
		dup2((ppl)->pp_outfile, STDOUT_FILENO);
		close_all_fds(&ppl);
		ppl->pp_heredoc_status = 0;
	}
	if (ppl->pp_red_status == 1)
		dup_red_fds(&ppl);
	return (EXIT_SUCCESS);
}
