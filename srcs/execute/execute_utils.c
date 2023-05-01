#include "../../headers/minishell.h"

void	close_fds(t_ppline **ppline)
{
	t_ppline	*pp_curr;

	pp_curr = *ppline;
	while (pp_curr)
	{
		if (pp_curr->pp_outfile > 2)
			close(pp_curr->pp_outfile);
		if (pp_curr->pp_infile > 2)
			close(pp_curr->pp_infile);
		pp_curr = pp_curr->next;
	}
}
