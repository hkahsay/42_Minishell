#include "../../headers/minishell.h"

t_ppl	*ft_new_ppl(void)
{
	t_ppl	*new_ppl;

	new_ppl = NULL;
	new_ppl = (t_ppl *)my_malloc(sizeof(t_ppl));
	if (new_ppl == NULL)
		return (NULL);
	new_ppl->pp_first_cmd = NULL;
	new_ppl->ppl_cmd = NULL;
	new_ppl->pp_arr_env = NULL;
	new_ppl->saved_stdin = -1;
	new_ppl->saved_stdout = -1;
	new_ppl->pp_red_status = 0;
	new_ppl->pp_fd_in = -1;
	new_ppl->pp_fd_out = -1;
	new_ppl->pp_infile = 0;
	new_ppl->pp_outfile = 1;
	new_ppl->pp_heredoc_status = 0;
	new_ppl->pp_heredoc_eof = NULL;
	new_ppl->pp_exit = 0;
	new_ppl->pp_list_env = NULL;
	new_ppl->next = NULL;
	return (new_ppl);
}
