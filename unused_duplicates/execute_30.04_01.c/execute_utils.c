#include "../../headers/minishell.h"

void	close_fds(t_ppline **ppline)
{
	t_ppline	*pp_curr;

	pp_curr = *ppline;
	while (pp_curr)
	{
		if (pp_curr->pp_outfile > 2)
			close(pp_curr->pp_outfile);
		if (pp_curr->pp_infile > 2)
			close(pp_curr->pp_infile);
		pp_curr = pp_curr->next;
	}
}

void	wait_execution(t_ppline **ppline)
{
	// int		res;
	// pid_t	pid;
	t_ppline	*pp_curr;

	// res = 1;
	pp_curr = *ppline;
	close_fds(ppline);
	while (pp_curr)
	{
		waitpid(pp_curr->pp_pid, &(pp_curr->pp_exit), 0);
		pp_curr = pp_curr->next;
	}
}
// 	while (ppline->ppline_cmd && ppline_idx > 0)
// 	{
// 		// ppline->pp_exit = wait_pid(&ppline->pp_pid);
// 		res = wait_status(&pid);
// 		init_pid(ppline, pid);
// 		ppline_idx--;
// 		if (ppline->next)
// 			ppline->ppline_cmd = ppline->next->ppline_cmd;
// 	}
// 	g_exit_status = res;
// 	// g_exit_status = ppline->pp_exit;
// 	return (g_exit_status);
// }


// static void	close_all_fd(t_ppline *ppline)
// {
// 	t_ppline	*pp_curr;

// 	pp_curr = ppline;
// 	while (ppline)
// 	{
// 		if ()
// 		close_fd(&pp_curr->pp_infile[0]);
// 		close_fd(&pp_curr->pp_pipe[1]);
// 		if (pp_curr->pp_id == TOK_REDIR_IN)
// 			close_fd(&ppline->pp_infile);
// 		if (pp_curr->pp_id == TOK_REDIR_OUT)
// 			close_fd(&ppline->pp_outfile);
// 		if (pp_curr->pp_id == TOK_HEREDOC)
// 			close_fd(&ppline->pp_heredoc_fd);
// 		if (pp_curr->pp_id == TOK_REDIR_OUT_APPEND)
// 			close_fd(&ppline->pp_append_fd);
// 		ppline = ppline->next;
// 	}
// }
