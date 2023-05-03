#include "../../headers/minishell.h"


void	*init_pipe(t_ppline **ppline, int *num_pipes) //, int *num_pipes
{
	t_ppline *pp_curr;
	int		fd[2];

	pp_curr = *ppline;
	// pp_curr->pp_infile = STDIN_FILENO;
	while (pp_curr->next)
	{
		if (pipe(fd) == -1)
			 msg_error("Failed to create pipe", errno);
		if (pp_curr->pp_outfile == 1)
			pp_curr->pp_outfile = fd[1];
		else
			close (fd[1]);
		if (pp_curr->next->pp_infile == 0)
			pp_curr->next->pp_infile = fd[0];
		else
			close (fd[0]);
		// if (pp_curr->next)
		pp_curr = pp_curr->next;
		(*num_pipes)++;
	}
	if (!pp_curr->pp_outfile)
		pp_curr->pp_outfile = STDOUT_FILENO;
	return (0);
}
