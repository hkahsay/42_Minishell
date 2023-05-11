#include "../../headers/minishell.h"

t_ppline	*ft_new_ppline(void)
{
	t_ppline	*new_ppline = NULL;
	new_ppline = (t_ppline *)my_malloc(sizeof(t_ppline));
	if (new_ppline == NULL)
		return NULL;
	new_ppline->pp_first_cmd = NULL;
	new_ppline->ppline_cmd = NULL;
	new_ppline->pp_arr_env = NULL;
	new_ppline->saved_stdin = -1;
	new_ppline->saved_stdout = -1;
	new_ppline->pp_red_status = 0;
	new_ppline->pp_fd_in = -1;
	new_ppline->pp_fd_out = -1;
	new_ppline->pp_infile = 0;
	new_ppline->pp_outfile = 1;
	new_ppline->pp_heredoc_status = 0;
	new_ppline->pp_heredoc_eof = NULL;
	new_ppline->pp_exit = 0;
	new_ppline->pp_list_env = NULL;
	new_ppline->next = NULL;
	return (new_ppline);
}
