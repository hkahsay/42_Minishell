#include "../../headers/minishell.h"

int	execute_kid(t_ppline *ppline)
{
	char	*cmd_path;

	cmd_path = NULL;
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
		ppline->pp_exit = execute_builtin(&ppline);
		return (ppline->pp_exit);
		// exit(0);
	}
	else
	{
		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
		{
			g_exit_status = 127;
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
		}
		if (!execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env))
			msg_error("error execution: ", errno);
	}
	return (EXIT_SUCCESS);
}
