#include "../../headers/minishell.h"

// int	execute_path_cmd(t_ppline *ppline)
// {
// 	char	*cmd_path;

// 	cmd_path = NULL;
// 	ppline->pp_pid = fork();
// 	if (ppline->pp_pid == 0)
// 	{
// 		if (check_if_builtin(ppline->pp_first_cmd) == 0)
// 		{
// 			if (ppline->pp_outfile != STDOUT_FILENO)
// 				dup2(ppline->pp_outfile, STDOUT_FILENO);
// 			if (ppline->pp_infile != STDIN_FILENO)
// 				dup2(ppline->pp_infile, STDIN_FILENO);
// 			close_all_fds(&ppline);
// 			ppline->pp_exit = execute_builtin(&ppline);
// 		}
// 		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
// 		{
// 			g_exit_status = 127;
// 			ft_putstr_fd("minishell: ", STDERR_FILENO);
// 			msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
// 		}
// 		if (ppline->pp_outfile != STDOUT_FILENO)
// 			dup2(ppline->pp_outfile, STDOUT_FILENO);
// 		if (ppline->pp_infile != STDIN_FILENO)
// 			dup2(ppline->pp_infile, STDIN_FILENO);
// 		close_all_fds(&ppline);
// 		execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
// 		msg_error("error execution: ", errno);
// 	}
// 	else
// 		close_fds(&ppline);
// 	return (0);
// }
