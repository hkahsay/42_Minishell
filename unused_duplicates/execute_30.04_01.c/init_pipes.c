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
	printf(LBLUE "\nEnter init_pipe OK\n" RS);
	printf(LBLUE "init_pipe: pp_curr->pp_infile %d\n" RS, pp_curr->pp_infile);
	printf(LBLUE "init_pipe: pp_curr->pp_outfile %d\n" RS, pp_curr->pp_outfile);
	while (pp_curr->next)
	{
		if (pipe(fd) == -1)
			 msg_error("Failed to create pipe", errno);
		printf(LBLUE "init_pipe: fd[0] %d\n" RS, fd[0]);
		printf(LBLUE "init_pipe: fd[1] %d\n" RS, fd[1]);
		if (pp_curr->pp_outfile == 1)
			pp_curr->pp_outfile = fd[1];
		if (pp_curr->next->pp_infile == 0)
			pp_curr->next->pp_infile = fd[0];
		if (pp_curr->next)
		pp_curr = pp_curr->next;
		(*num_pipes)++;
	}
	if (pp_curr->pp_outfile == 0)
		pp_curr->pp_outfile = STDOUT_FILENO;
	printf(LBLUE "Exit init_pipe: pp_curr->pp_infile %d\n" RS, pp_curr->pp_infile);
	printf(LBLUE "Exit init_pipe: pp_curr->pp_outfile %d\n" RS, pp_curr->pp_outfile);
	printf(LBLUE "Exit num_pipes: %d\n" RS, (*num_pipes));
	printf(LBLUE "Exit init_pipe OK\n\n" RS);
	return (0);
}
