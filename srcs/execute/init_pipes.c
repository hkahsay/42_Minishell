#include "../../headers/minishell.h"

void	*init_pipe(t_ppline **ppline, int ppline_idx)
{
	int		pipes[2];
	int		i;

	t_ppline *first;
	first = *ppline;
	i = 0;
	if (ppline_idx == 1)
	 	return (0);
	while ((*ppline)->next && i < ppline_idx)
	{
		if (pipe(pipes) == -1)
			 msg_error("minishell_VH: failed to create pipe", errno);
		if ((*ppline)->pp_outfile == 1)
		{
			(*ppline)->pp_outfile = pipes[1];
			(*ppline)->next->pp_infile = pipes[0];
		}
		else
		{
			close((*ppline)->next->pp_infile);
			close((*ppline)->pp_outfile);
		}
		*ppline = (*ppline)->next;
		i++;
	}
	*ppline = first;
	return (0);
}
