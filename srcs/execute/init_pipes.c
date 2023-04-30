#include "../../headers/minishell.h"

/*
int **init_pipes(int nb_pipes)
{
	int pipes[nb_pipes][2];

	int i = 0;
	while (i < nb_pipes)
	{
		pipe(pipes[i]);
		++i;
	}
	return pipes;
}
*/

void	*init_pipe(t_ppline **ppline, int *num_pipes) //, int *num_pipes
{
	t_ppline *pp_curr;
	int		fd[2];

	pp_curr = *ppline;
	while (pp_curr->next)
	{
		if (pipe(fd) == -1)
			 msg_error("Failed to create pipe", errno);
		if (pp_curr->pp_outfile == 1)
		{
			pp_curr->pp_outfile = fd[1];
			close (fd[1]);
		}
		if (pp_curr->next->pp_infile == 0)
		{
			pp_curr->next->pp_infile = fd[0];
			close (fd[0]);
		}
		if (pp_curr->next)
		pp_curr = pp_curr->next;
		(*num_pipes)++;
	}
	if (pp_curr->pp_outfile == 0)
		pp_curr->pp_outfile = STDOUT_FILENO;
	return (0);
}
