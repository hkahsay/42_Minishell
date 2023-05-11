#include "../../headers/minishell.h"

// void	close_all_fds(t_ppl **ppl)
// {
// 	t_ppl	*pp_curr;

// 	pp_curr = *ppl;
// 	while (pp_curr)
// 	{
// 		if (pp_curr->pp_infile != STDIN_FILENO)
// 			close(pp_curr->pp_infile);
// 		if (pp_curr->pp_outfile != STDOUT_FILENO)
// 			close(pp_curr->pp_outfile);
// 		pp_curr = pp_curr->next;
// 	}
// }
