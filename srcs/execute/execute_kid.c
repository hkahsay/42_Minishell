#include "../../headers/minishell.h"

int	execute_path_cmd(t_ppline *ppline)
{
	char	*cmd_path;
	// pid_t	kid_pid;
	// pid_t wpid;
	// int		exit_status;

	cmd_path = NULL;
	// printf(ORS "EXECUTE KID: forked path_cmd ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);
	ppline->pp_pid = fork();
	// printf(PURPLE "kid_pid after fork: %d\n" RS, kid_pid);
	if (ppline->pp_pid == 0)
	{
		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
		{
			g_exit_status = 127;
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
		}
		// for (int i = 0; (ppline)->ppline_cmd[i]; i++)
		// 	printf("\nCmd[%d]: %s\n\n", i, (ppline)->ppline_cmd[i]);
		// printf("Out is default: %d\n", (ppline->pp_outfile == STDOUT_FILENO));
		printf("In is %d\n", ppline->pp_infile);
		printf("Out is %d\n", ppline->pp_outfile);
		if (ppline->pp_outfile != STDOUT_FILENO)
			dup2(ppline->pp_outfile, STDOUT_FILENO);
		if (ppline->pp_infile != STDIN_FILENO)
			dup2(ppline->pp_infile, STDIN_FILENO);
		close_all_fds(&ppline);
		execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
		msg_error("error execution: ", errno);
	}
	else
	{
		printf("INFILE: %d\n", ppline->pp_infile);
		printf("OUTFILE: %d\n", ppline->pp_outfile);
		printf("Pid: %d\n", ppline->pp_pid);
		close_fds(&ppline);
	}
	// else
	// {
	// 	close_fds(&ppline);
	// 	(ppline)->pp_pid = kid_pid;

	// 	printf(PURPLE "PID execve parent: %d\n" RS, ppline->pp_pid);
	// 	waitpid(ppline->pp_pid, &(ppline->pp_exit), 0);
	// 	printf(R "\nPID execve parent waited\n\n" RS);
	// }
	// if (WIFEXITED(exit_status))
	// {
	// 	printf(R "\nWIFEXITED\n\n" RS);
	// 	ppline->pp_exit = WEXITSTATUS(exit_status);
	// 	printf(R "PID execve parent: %d\n" RS, ppline->pp_exit );
	// }
	// exit(0);
	return (0);
}

// int	execute_kid(t_ppline *ppline)
// {
// 	// int	saved_stdin;
// 	// int	saved_stdout;
// 	// char	*cmd_path;
// 	// cmd_path = NULL;
// 	printf(ORS "EXECUTE KID: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);

// 	// saved_stdin = dup(STDIN_FILENO);
// 	// saved_stdout = dup(STDOUT_FILENO);
// 	// if (ppline->pp_infile > 2)
// 	// {
// 	// 	dup2(ppline->pp_infile, STDIN_FILENO);
// 	// 	close(ppline->pp_infile);
// 	// }
// 	// if (ppline->pp_outfile > 2)
// 	// {
// 	// 	dup2(ppline->pp_outfile, STDOUT_FILENO);
// 	// 	close(ppline->pp_outfile);
// 	// }
// 	// close_fds(&(ppline->first));
// 	printf (YELS"new_ppline->pp_infile: %d\n" RS, ppline->pp_infile);
// 	printf (YELS"new_ppline->pp_outfile: %d\n" RS, ppline->pp_outfile);

// 	if (ppline)
// 	{
// 		if (check_if_builtin(ppline->pp_first_cmd) == 0)
// 		{
// 			ppline->pp_exit = execute_builtin(&ppline);
// 			return (ppline->pp_exit);
// 			exit(0);
// 		}
// 		else
// 		{
// 			if (execute_path_cmd(ppline)) //execute_path_cmd
// 				msg_error("error executing path_cmd: ", errno);
// 		// 	if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
// 		// 	{
// 		// 		g_exit_status = 127;
// 		// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		// 		msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
// 		// 	}
// 		// 	// execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
// 		// 	if (!execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env))
// 		// 		msg_error("error execution: ", errno);
// 		// // }

// 			else
// 			{
// 				close_fds(&ppline);
// 			}

// 		}
// 	// dup2(saved_stdin, STDIN_FILENO);
// 	// dup2(saved_stdout, STDOUT_FILENO);
// 	// close(saved_stdin);
// 	// close(saved_stdout);
// 	}
// 	return (EXIT_SUCCESS);
// 	// exit(0);
// }

	// 	if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
	// 	{
	// 		g_exit_status = 127;
	// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
	// 		msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
	// 	}
	// 	if (!execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env))
	// 		msg_error("error execution: ", errno);
	// }
