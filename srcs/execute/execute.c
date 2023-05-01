#include "../../headers/minishell.h"

void	close_fds(t_ppline **ppline)
{
	t_ppline	*pp_curr;

	pp_curr = *ppline;
	while (pp_curr)
	{
		if (pp_curr->pp_infile > 2)
			close(pp_curr->pp_infile);
		if (pp_curr->pp_outfile > 2)
			close(pp_curr->pp_outfile);
		pp_curr = pp_curr->next;
	}
}

void	wait_execution(t_ppline **ppline)
{
	t_ppline	*pp_curr;

	pp_curr = *ppline;
	close_fds(ppline);
	while (pp_curr)
	{
		// printf (YELLOW "PIPE PARENT PID: %d\n" RS, pp_curr->pp_pid);
		close_fds(ppline);
		waitpid(pp_curr->pp_pid, &(pp_curr->pp_exit), 0);
		pp_curr = pp_curr->next;
	}
}

int	execute_pipe_loop(t_ppline *ppline)
{
	t_ppline	*pp_curr;
	int			num_pipes = 0;

	pp_curr = ppline;
	init_pipe(&pp_curr, &num_pipes);
	// printf (YELLOW "PIPES num: %d\n" RS, num_pipes);
	while (pp_curr && num_pipes >= 0)
	{
		// printf(ORS "EXECUTE: ppline->pp_first_cmd %s\n" RS, pp_curr->pp_first_cmd);
		if (pp_curr->pp_infile < 0 || pp_curr->pp_outfile < 0)
		{
			pp_curr = pp_curr->next;
			continue ;
		}
		pp_curr->pp_pid = fork();
		//  printf (YELLOW "PIPE PARENT PID: %d\n" RS, pp_curr->pp_pid);
		if (pp_curr->pp_pid == -1)
			msg_error("error redir: ", errno);
		if (pp_curr->pp_pid == 0) //child
		{
			// printf(ORS "EXECUTE: send to execut kid ppline->pp_first_cmd %s\n" RS, pp_curr->pp_first_cmd);
			execute_kid(pp_curr);
		}
		// close_fds(&pp_curr);
		pp_curr = pp_curr->next;
		num_pipes--;
	}
	wait_execution(&ppline);
	return (EXIT_SUCCESS);
}

void execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;

	print_cmd_list(cmd);
	ppline = build_ppline_array(&cmd, cmd_num, mini_env);

	signal(SIGINT, sig_quit_handler);
	signal(SIGQUIT, sig_quit_handler);
	// error input pipe, already handled
	if (ppline->ppline_idx == 1 && ppline->pp_red_status == 0 && check_if_builtin(ppline->pp_first_cmd) == 0)
	{
		ppline->pp_exit = execute_builtin(&ppline);
		g_exit_status = ppline->pp_exit;
		return ;
	}
	else
		ppline->pp_exit = execute_pipe_loop(ppline);
	wait_execution(&ppline);
	// close_fds(&ppline);
}
