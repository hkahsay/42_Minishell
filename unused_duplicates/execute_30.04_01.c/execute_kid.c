#include "../../headers/minishell.h"

int	execute_kid(t_ppline *ppline)
{
	printf(YELLOW "Execution kid\n" RS);
	// int	stdin_clone;
	// int	stdout_clone;

	// stdin_clone = dup(STDIN_FILENO);
	// stdout_clone = dup(STDOUT_FILENO);
	if (ppline->pp_infile > 2)
	{
		dup2(ppline->pp_infile, STDIN_FILENO);
		close(ppline->pp_infile);
	}
	if (ppline->pp_outfile > 2)
	{
		dup2(ppline->pp_outfile, STDOUT_FILENO);
		close(ppline->pp_outfile);
	}
	if (check_if_builtin(ppline->pp_first_cmd) == 0)
	{
		printf(YELLOW "Execution kid builtin_cmd\n" RS);
		ppline->pp_exit = execute_builtin(&ppline); //execute_single_builtin(ppline)
		return (ppline->pp_exit);
		exit(0);
	}
	else
	{
		printf(YELLOW "Execution kid no_builtin path_cmd\n\n" RS);
		if (!execute_path_cmd(ppline)) //execute_path_cmd
			msg_error("error executing path_cmd: ", errno);
		// return (0);
		// exit(0);
	}
	// close_fds(&ppline);
	// exit(0);
	return (EXIT_SUCCESS);
}
