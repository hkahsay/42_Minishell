#include "../../headers/minishell.h"

// static void	execute_search_path(t_ppline **curr_ppline)
// {
// 	char	*cmd_path;
// 	// pid_t	kid_pid;
// 	// pid_t wpid;
// 	// int		exit_status;
// 	t_ppline	*ppline = *curr_ppline;
// 	cmd_path = NULL;
// 	if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
// 	{
// 		g_exit_status = 127;
// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
// 	}
// 	// for (int i = 0; (ppline)->ppline_cmd[i]; i++)
// 	// 	printf("\nCmd[%d]: %s\n\n", i, (ppline)->ppline_cmd[i]);
// 	// printf("Out is default: %d\n", (ppline->pp_outfile == STDOUT_FILENO));
// 	printf("In path cmd is %d\n", ppline->pp_infile);
// 	printf("Out path cmd is %d\n", ppline->pp_outfile);
// 	if (ppline->pp_outfile != STDOUT_FILENO)
// 		dup2(ppline->pp_outfile, STDOUT_FILENO);
// 	if (ppline->pp_infile != STDIN_FILENO)
// 		dup2(ppline->pp_infile, STDIN_FILENO);
// 	close_all_fds(&ppline);
// 	execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
// 	msg_error("error execution: ", errno);
// }

void	close_red_fds(t_ppline **ppline)
{
	if ((*ppline)->pp_fd_out != STDOUT_FILENO)
	{
		printf("CLOSE OF pp_fd_out\n");
		close((*ppline)->pp_fd_out);
	}
	if ((*ppline)->pp_fd_in != STDIN_FILENO)
	{
		printf("CLOSE OF pp_fd_in \n");
		close((*ppline)->pp_fd_in);
	}
}


//echo: write: Bad file descriptor

int	execute_path_cmd(t_ppline *ppline)
{
	char	*cmd_path;
	// int		fd[2];
	// char	*line;
	// // pid_t	kid_pid;
	// // pid_t wpid;
	// // int		exit_status;

	cmd_path = NULL;
	// printf(ORS "EXECUTE KID: forked path_cmd ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);
	ppline->pp_pid = fork();
	// printf(PURPLE "kid_pid after fork: %d\n" RS, kid_pid);
	if (ppline->pp_pid == 0)
	{
		// if (ppline->pp_heredoc_status == 1)
		// 	execute_heredoc(ppline);
		// if (ppline->pp_heredoc_status == 1)
		// {
		// 	pipe(fd);
		// 	while (1)
		// 	{
		// 		line = readline("> ");

		// 		if (line == NULL || !(ft_strcmp((ppline)->pp_heredoc_eof, line)))
		// 			break ;
		// 		ft_putendl_fd(line, fd[1]);
		// 	}
		// 	close(fd[1]);
		// 	(ppline)->pp_fd_in = fd[0];
		// 	// close(fd[0]);
		// 	// printf("HEREDOC FD pp_fd_in after heredoc: %d\n" RS, (ppline)->pp_fd_in);
		// 	// printf("HEREDOC FD pp_fd_out after heredoc: %d\n" RS, (ppline)->pp_fd_out);
		// 	// if (ppline->pp_outfile != ppline->pp_fd_out)
		// 	// 	dup2(ppline->pp_outfile, ppline->pp_fd_out);
		// 	// if (ppline->pp_infile != ppline->pp_fd_in)
		// 	// 	dup2(ppline->pp_infile, ppline->pp_fd_in);
		// 	// printf ("HEREDOC after dup2: infile: %d\n" RS, ppline->pp_infile);
		// 	// printf ("HEREDOC after dup2: outfile: %d\n" RS, ppline->pp_outfile);
		// 	// printf ("HEREDOC after dup2: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
		// 	// printf ("HEREDOC after dup2: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
		// 	// close_red_fds(&ppline);
		// 	ppline->pp_heredoc_status = 0;
		// }
		// if (ppline->pp_heredoc_status == 1)
		// {
		// 	pipe(fd);
		// 	while (1)
		// 	{
		// 		line = readline("> ");

		// 		if (line == NULL || !(ft_strcmp((ppline)->pp_heredoc_eof, line)))
		// 			break ;
		// 		ft_putendl_fd(line, fd[1]);
		// 	}
		// 	// (ppline)->pp_fd_in = fd[0];
		// 	printf("HEREDOC before fd[1]: %d\n" RS, fd[1]);
		// 	printf("HEREDOC before fd[0]: %d\n" RS, fd[0]);
		// 	if (!ppline->pp_first_cmd)
		// 	{
		// 		close(fd[1]);
		// 		close(fd[0]);
		// 	}
		// 	printf("HEREDOC after fd[1]: %d\n" RS, fd[1]);
		// 	printf("HEREDOC after fd[0]: %d\n" RS, fd[0]);
		// 	// if (ppline->pp_outfile != ppline->pp_fd_out)
		// 	dup2(ppline->pp_infile, fd[0]);
		// 	dup2(ppline->pp_outfile, fd[1]);
		// 	close(fd[1]);
		// 	close(fd[0]);
		// 	// if (ppline->pp_infile != ppline->pp_fd_in)
		// 	// 	dup2(ppline->pp_infile, ppline->pp_fd_in);
		// 	printf ("HEREDOC after dup2: infile: %d\n" RS, ppline->pp_infile);
		// 	printf ("HEREDOC after dup2: outfile: %d\n" RS, ppline->pp_outfile);
		// 	// printf ("HEREDOC after dup2: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
		// 	// printf ("HEREDOC after dup2: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
		// 	// close_red_fds(&ppline);
		// 	ppline->pp_heredoc_status = 0;
		// }
		if (check_if_builtin(ppline->pp_first_cmd) == 0)
		{
			printf(R"\nbuiltin\n"RS);
			printf("In builtin cmd is %d\n", ppline->pp_infile);
			printf("Out builtin cmd is %d\n", ppline->pp_outfile);
			// if (ppline->pp_red_status == 1)
			// {
			// 	printf(YELLOW"\nbuiltin ppline->pp_red_status == 1\n"RS);
			// 	printf ("after pp_red_status == 1: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			// 	printf ("after pp_red_status == 1: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			// 	if (ppline->pp_fd_out != STDOUT_FILENO)
			// 	{
			// 		printf(R"\ndup2(ppline->pp_fd_out)\n"RS);
			// 		dup2(ppline->pp_fd_out, STDOUT_FILENO);
			// 	}
			// 	if (ppline->pp_fd_in != STDIN_FILENO)
			// 	{
			// 		printf(R"\ndup2(ppline->pp_fd_in)\n"RS);
			// 		dup2(ppline->pp_fd_in, STDIN_FILENO);
			// 	}
			// 	printf(LB"\nafter dup2 before close\n"RS);
			// 	close_red_fds(&ppline);
			// 	printf (GREEN"after pp_red_status == 1: infile: %d\n" RS, ppline->pp_infile);
			// 	printf ("after pp_red_status == 1: outfile: %d\n" RS, ppline->pp_outfile);
			// 	printf ("after pp_red_status == 1: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			// 	printf ("after pp_red_status == 1: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			// 	if (ppline->pp_outfile != ppline->pp_fd_out)
			// 		dup2(ppline->pp_outfile, ppline->pp_fd_out);
			// 	if (ppline->pp_infile != ppline->pp_fd_in)
			// 		dup2(ppline->pp_infile, ppline->pp_fd_in);
			// 	// if (ppline->pp_fd_out != ppline->pp_outfile)
			// 	// 	dup2(ppline->pp_fd_out, ppline->pp_outfile);
			// 	// if (ppline->pp_fd_in != ppline->pp_infile)
			// 	// 	dup2(ppline->pp_fd_in, ppline->pp_infile);	
			// 	printf ("after dup2: infile: %d\n" RS, ppline->pp_infile);
			// 	printf ("after dup2: outfile: %d\n" RS, ppline->pp_outfile);
			// 	printf ("after dup2: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			// 	printf ("after dup2: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			// 	close_fds(&ppline);
			// }
			if (ppline->pp_outfile != STDOUT_FILENO)
				dup2(ppline->pp_outfile, STDOUT_FILENO);
			if (ppline->pp_infile != STDIN_FILENO)
				dup2(ppline->pp_infile, STDIN_FILENO);
			close_all_fds(&ppline);
			ppline->pp_exit = execute_builtin(&ppline);
			// return (0);
			// return (ppline->pp_exit);
			// exit(0);
			// close_fds(&ppline);
		}

		// else
		// {

			if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
			{
				g_exit_status = 127;
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
			}
			// if (ppline->pp_red_status == 1)
			// {
			// 	printf(YELLOW"\nbuiltin ppline->pp_red_status == 1\n"RS);
			// 	printf ("after pp_red_status == 1: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			// 	printf ("after pp_red_status == 1: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			// 	if (ppline->pp_fd_out != STDOUT_FILENO)
			// 	{
			// 		printf(R"\ndup2(ppline->pp_fd_out)\n"RS);
			// 		dup2(ppline->pp_fd_out, STDOUT_FILENO);
			// 	}
			// 	if (ppline->pp_fd_in != STDIN_FILENO)
			// 	{
			// 		printf(R"\ndup2(ppline->pp_fd_in)\n"RS);
			// 		dup2(ppline->pp_fd_in, STDIN_FILENO);
			// 	}
			// 	printf(LB"\nafter dup2 before close\n"RS);
			// 	close_red_fds(&ppline);
			// 	printf (GREEN"after pp_red_status == 1: infile: %d\n" RS, ppline->pp_infile);
			// 	printf ("after pp_red_status == 1: outfile: %d\n" RS, ppline->pp_outfile);
			// 	printf ("after pp_red_status == 1: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			// 	printf ("after pp_red_status == 1: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			// 	if (ppline->pp_outfile != ppline->pp_fd_out)
			// 		dup2(ppline->pp_outfile, ppline->pp_fd_out);
			// 	if (ppline->pp_infile != ppline->pp_fd_in)
			// 		dup2(ppline->pp_infile, ppline->pp_fd_in);
			// 	printf ("after dup2: infile: %d\n" RS, ppline->pp_infile);
			// 	printf ("after dup2: outfile: %d\n" RS, ppline->pp_outfile);
			// 	printf ("after dup2: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			// 	printf ("after dup2: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			// 	close_fds(&ppline);
			// }
			// 	if (ppline->pp_heredoc_status == 1)
			// {
			// 	pipe(fd);
			// 	while (1)
			// 	{
			// 		line = readline("> ");

			// 		if (line == NULL || !(ft_strcmp((ppline)->pp_heredoc_eof, line)))
			// 			break ;
			// 		ft_putendl_fd(line, fd[1]);
			// 	}
			// 	close(fd[1]);
			// 	(ppline)->pp_fd_in = fd[0];
			// 	close(fd[0]);
			// 	printf("HEREDOC FD pp_fd_in after heredoc: %d\n" RS, (ppline)->pp_fd_in);
			// 	printf("HEREDOC FD pp_fd_out after heredoc: %d\n" RS, (ppline)->pp_fd_out);
			// 	if (ppline->pp_outfile != ppline->pp_fd_out)
			// 		dup2(ppline->pp_outfile, ppline->pp_fd_out);
			// 	if (ppline->pp_infile != ppline->pp_fd_in)
			// 		dup2(ppline->pp_infile, ppline->pp_fd_in);
			// 	printf ("HEREDOC after dup2: infile: %d\n" RS, ppline->pp_infile);
			// 	printf ("HEREDOC after dup2: outfile: %d\n" RS, ppline->pp_outfile);
			// 	printf ("HEREDOC after dup2: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			// 	printf ("HEREDOC after dup2: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			// 	close_fds(&ppline);
			// }
			// for (int i = 0; (ppline)->ppline_cmd[i]; i++)
			// 	printf("\nCmd[%d]: %s\n\n", i, (ppline)->ppline_cmd[i]);
			// printf("Out is default: %d\n", (ppline->pp_outfile == STDOUT_FILENO));
			printf("In path cmd is %d\n", ppline->pp_infile);
			printf("Out path cmd is %d\n", ppline->pp_outfile);
			if (ppline->pp_outfile != STDOUT_FILENO)
				dup2(ppline->pp_outfile, STDOUT_FILENO);
			if (ppline->pp_infile != STDIN_FILENO)
				dup2(ppline->pp_infile, STDIN_FILENO);
			close_all_fds(&ppline);
			execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
			msg_error("error execution: ", errno);
		// }
	}
	else
	{
		printf(GREEN"INFILE finish kid: %d\n" RS, ppline->pp_infile);
		printf(GREEN"OUTFILE finish kid: %d\n"RS, ppline->pp_outfile);
		printf(GREEN"Pid finish kid: %d\n"RS, ppline->pp_pid);
		close_fds(&ppline);
	}
	return (0);
}
