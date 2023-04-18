#include "../../headers/minishell.h"

t_ppline	*ft_new_ppline(void) //t_cmd **cmd_ptr, 
{
	t_ppline	*new_ppline = NULL;
	new_ppline = (t_ppline *)malloc(sizeof(t_ppline));
	if (new_ppline == NULL)
		return NULL;
	new_ppline->pp_first_cmd = NULL;
	new_ppline->ppline_cmd = NULL;
	new_ppline->ppline_env = NULL;
	// new_ppline->ppline_idx = cmd_index;
	new_ppline->red_status = 0;
	new_ppline->infile = -1;
	new_ppline->outfile = -1;
	new_ppline->heredoc = 0;
	new_ppline->hdoc_fd[0] = -1;
	new_ppline->hdoc_fd[1] = -1;
	new_ppline->exit_status = 0;
	new_ppline->next = NULL;
	// printf(YELLOW "PPline after init\n" RS);
	return (new_ppline);
}
