#include "../../headers/minishell.h"

// void	close_all_fds(t_ppline **ppline)
// {
// 	t_ppline	*pp_curr;

// 	pp_curr = *ppline;
// 	while (pp_curr)
// 	{
// 		if (pp_curr->pp_infile != STDIN_FILENO)
// 			close(pp_curr->pp_infile);
// 		if (pp_curr->pp_outfile != STDOUT_FILENO)
// 			close(pp_curr->pp_outfile);
// 		pp_curr = pp_curr->next;
// 	}
// }
