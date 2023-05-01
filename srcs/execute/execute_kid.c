#include "../../headers/minishell.h"

int	execute_path_cmd(t_ppline *ppline)
{
	char	*cmd_path;
	pid_t	kid_pid;
	int		exit_status;

	cmd_path = NULL;
	// printf(ORS "EXECUTE KID: forked path_cmd ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);
	kid_pid = fork();
	// printf(PURPLE "kid_pid after fork: %d\n" RS, kid_pid);
	if (kid_pid == 0)
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
	else
	{
		// printf(PURPLE "kid_pid before waitpid: %d\n" RS, kid_pid);
		waitpid(kid_pid, &(ppline->pp_exit), 0);
	}
	if (WIFEXITED(exit_status))
		ppline->pp_exit = WEXITSTATUS(exit_status);
	return (0);
}

int	execute_kid(t_ppline *ppline)
{
	// printf(ORS "EXECUTE KID: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);

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
		if (execute_path_cmd(ppline)) //execute_path_cmd
			msg_error("error executing path_cmd: ", errno);
	}
	close_fds(&ppline);
	if (!ppline->pp_outfile)
		ppline->pp_outfile = STDOUT_FILENO;
	exit(0);
}

	// 	if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
	// 	{
	// 		g_exit_status = 127;
	// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
	// 		msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
	// 	}
	// 	if (!execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env))
	// 		msg_error("error execution: ", errno);
	// }
