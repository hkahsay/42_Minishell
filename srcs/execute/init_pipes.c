#include "../../headers/minishell.h"

static void	attribute_pipes(t_ppl **ppl, int *pipe1, int *pipe2)
{
	(*ppl)->next->pp_infile = *pipe1;
	(*ppl)->pp_outfile = *pipe2;
}

static void	close_pipes(t_ppl **ppl)
{
	close((*ppl)->next->pp_infile);
	close((*ppl)->pp_outfile);
}

void	*init_pipe(t_ppl **p_ppl, int ppl_idx)
{
	int		pipes[2];
	int		i;
	t_ppl	*ppl;
	t_ppl	*first;

	ppl = *p_ppl;
	first = *p_ppl;
	i = 0;
	if (ppl_idx == 1)
		return (0);
	while (ppl->next && i < ppl_idx)
	{
		if (pipe(pipes) == -1)
			msg_error("minishell_VH: failed to create pipe", errno);
		if (ppl->pp_outfile == 1)
			attribute_pipes(&ppl, &pipes[0], &pipes[1]);
		else
			close_pipes(&ppl);
		ppl = ppl->next;
		i++;
	}
	ppl = first;
	return (0);
}
