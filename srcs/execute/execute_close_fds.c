#include "../../headers/minishell.h"

void	close_red_fds(t_ppl **ppl)
{
	if ((*ppl)->pp_fd_out != -1)
		close((*ppl)->pp_fd_out);
	if ((*ppl)->pp_fd_in != -1)
		close((*ppl)->pp_fd_in);
}

void	close_fds(t_ppl **ppl)
{
	if (*ppl)
	{
		if ((*ppl)->pp_outfile != STDOUT_FILENO)
			close((*ppl)->pp_outfile);
		if ((*ppl)->pp_infile != STDIN_FILENO)
			close((*ppl)->pp_infile);
	}
}

void	close_all_fds(t_ppl **ppl)
{
	t_ppl	*pp_curr;

	pp_curr = *ppl;
	while (pp_curr)
	{
		if (pp_curr->pp_infile != STDIN_FILENO)
			close(pp_curr->pp_infile);
		if (pp_curr->pp_outfile != STDOUT_FILENO)
			close(pp_curr->pp_outfile);
		pp_curr = pp_curr->next;
	}
}

void	close_saved_stds(t_ppl **ppl)
{
	close((*ppl)->saved_stdin);
	close((*ppl)->saved_stdout);
}
