#include "../../headers/minishell.h"

void	*init_pipe(t_ppl **ppl, int ppl_idx)
{
	int		pipes[2];
	int		i;

	t_ppl *first;
	first = *ppl;
	i = 0;
	if (ppl_idx == 1)
	 	return (0);
	while ((*ppl)->next && i < ppl_idx)
	{
		if (pipe(pipes) == -1)
			 msg_error("minishell_VH: failed to create pipe", errno);
		if ((*ppl)->pp_outfile == 1)
		{
			(*ppl)->pp_outfile = pipes[1];
			(*ppl)->next->pp_infile = pipes[0];
		}
		else
		{
			close((*ppl)->next->pp_infile);
			close((*ppl)->pp_outfile);
		}
		*ppl = (*ppl)->next;
		i++;
	}
	*ppl = first;
	return (0);
}
