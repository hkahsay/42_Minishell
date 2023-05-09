#include "../../headers/minishell.h"

t_ppline	*ft_new_ppline(void) //t_cmd **cmd_ptr,
{
	t_ppline	*new_ppline = NULL;
	new_ppline = (t_ppline *)my_malloc(sizeof(t_ppline));
	printf(LB "new_ppline %p \n" RS, new_ppline);
	if (new_ppline == NULL)
		return NULL;
	new_ppline->pp_first_cmd = NULL;
	new_ppline->ppline_cmd = NULL;
	new_ppline->pp_arr_env = NULL;
	// new_ppline->ppline_idx = cmd_index;
	new_ppline->pp_red_status = 0;
	// new_ppline->pp_pipe[0] = -1;
	// new_ppline->pp_pipe[1] = -1;
	new_ppline->pp_infile = 0;
	// printf (YELS"new_ppline->pp_infile: %d\n" RS, new_ppline->pp_infile);
	new_ppline->pp_outfile = 1;
	// printf (YELS"new_ppline->pp_outfile: %d\n" RS, new_ppline->pp_outfile);
	new_ppline->pp_heredoc_status = 0;
	new_ppline->pp_heredoc_eof = NULL;
	new_ppline->pp_fd_in = -1;
	new_ppline->pp_fd_out = -1;
	new_ppline->pp_exit = 0;
	new_ppline->pp_list_env = NULL;
	new_ppline->next = NULL;
	// printf(YELLOW "PPline after init\n" RS);
	return (new_ppline);
}
