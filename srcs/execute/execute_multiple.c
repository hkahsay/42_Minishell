#include "../../headers/minishell.h"

// void	close_fds(t_ppline **ppline)
// {
// 	t_ppline	*pp_curr;

// 	pp_curr = *ppline;
// 	while (pp_curr)
// 	{
// 		if (pp_curr->pp_outfile > 2)
// 			close(pp_curr->pp_outfile);
// 		if (pp_curr->pp_infile > 2)
// 			close(pp_curr->pp_infile);
// 		pp_curr = pp_curr->next;
// 	}
// }

void	wait_execution(t_ppline **ppline)
{
	t_ppline	*pp_curr;

	pp_curr = *ppline;
	close_fds(ppline);
	while (pp_curr)
	{
		waitpid(pp_curr->pp_pid, &(pp_curr->pp_exit), 0);
		// close_fds(ppline);
		pp_curr = pp_curr->next;
	}
}

int	execute_multi_cmd(t_ppline *ppline)
{
	t_ppline	*pp_curr;
	int			num_pipes = 0;

	pp_curr = ppline;
	init_pipe(&pp_curr, &num_pipes);
	// if (num_pipes == 0)
	// 	execute_path_cmd(pp_curr);
	while (pp_curr)
	{
		if (pp_curr->pp_infile < 0 || pp_curr->pp_outfile < 0)
		{
			pp_curr = pp_curr->next;
			continue ;
		}
		pp_curr->pp_pid = fork();
		if (pp_curr->pp_pid == -1)
			msg_error("error redir: ", errno);
		if (pp_curr->pp_pid == 0) //child
		{
			
			execute_kid(pp_curr);
		}
		close_fds(&ppline);
		pp_curr = pp_curr->next;
	}
	// wait_execution(&pp_curr);
	return (EXIT_SUCCESS);
}