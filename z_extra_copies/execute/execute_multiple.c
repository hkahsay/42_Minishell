#include "../../headers/minishell.h"
void	close_all_fds(t_ppline **ppline)
{
	t_ppline	*pp_curr;

	pp_curr = *ppline;
	while (pp_curr)
	{
		if (pp_curr->pp_infile != STDIN_FILENO)
			close(pp_curr->pp_infile);
		if (pp_curr->pp_outfile != STDOUT_FILENO)
			close(pp_curr->pp_outfile);
		pp_curr = pp_curr->next;
	}
}

void	close_fds(t_ppline **ppline)
{
	if ((*ppline)->pp_outfile != STDOUT_FILENO)
	{
		// printf("CLOSE OF OUT\n");
		close((*ppline)->pp_outfile);
	}
	if ((*ppline)->pp_infile != STDIN_FILENO)
	{
		// printf("CLOSE OF IN\n");
		close((*ppline)->pp_infile);
	}
}

void	execute_parent(t_ppline **ppline)
{
	t_ppline	*pp_curr;
	int			i;

	i = 0;
	pp_curr = *ppline;
	close_all_fds(ppline);
	while (pp_curr && i < pp_curr->ppline_idx)
	{
		// waitpid(pp_curr->pp_pid, &(pp_curr->pp_exit), 0);
		printf(LB"PPCURR: %d\n" RS, pp_curr->pp_pid);
		if (pp_curr->pp_pid != 0)
		{
			waitpid(pp_curr->pp_pid, &g_exit_status, 0);
			if (WIFSIGNALED(g_exit_status))
				g_exit_status = 128 + g_exit_status;
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
		}
		if (pp_curr->next)
		{
			i++;
			pp_curr = pp_curr->next;
		}
		else
		{
			printf(LB"Break\n"RS);
			break ;
		}
	}
}

static void	*init_pipe(t_ppline **ppline, int ppline_idx) //, int *num_pipes
{
	int		pipes[2];
	int		i;

	t_ppline *first;
	first = *ppline;
	i = 0;
	if (ppline_idx == 1)
	 	return (0);
	// pp_curr->pp_infile = STDIN_FILENO;
	while ((*ppline)->next && i < ppline_idx)
	{
		if (pipe(pipes) == -1)
			 msg_error("Failed to create pipe", errno);
		// if (pp_curr->pp_outfile = 1)
		printf (GREEN"%d: pipes[0]: %d\n" RS, i, pipes[0]);
		printf (GREEN"%d: pipes[1]: %d\n" RS, i, pipes[1]);
		// execute_kid(ppline);
		(*ppline)->pp_outfile = pipes[1];
		printf("PPLINE: %p\n", *ppline);
		// printf(YELLOW "PPLINE: %s\n" RS, (*ppline)->ppline_cmd[i]);
		// printf (GREEN"(*ppline)->pp_outfile: %d\n" RS, (*ppline)->pp_outfile);
		// dup2((*ppline)->pp_outfile, STDOUT_FILENO);
		// printf("1pok\n");
		// close ((*ppline)->pp_outfile);
		// printf("2pok\n");

		// printf (GREEN"pipes[1]: %d\n" RS, pipes[1]);
		// close (pipes[0]);
		(*ppline)->next->pp_infile = pipes[0];
		// printf (GREEN"(*ppline)->next->pp_infile: %d\n" RS, (*ppline)->next->pp_infile);
		// dup2((*ppline)->next->pp_infile, STDIN_FILENO);
		// close ((*ppline)->next->pp_infile);
		// close (pipes[1]);
		// close_fds(ppline);
		*ppline = (*ppline)->next;
		i++;
	}
	*ppline = first;
	return (0);
}

void	dup_fds(t_ppline **ppline)
{
	printf("1ok\n");
	if((*ppline)->pp_infile != STDIN_FILENO)
		dup2((*ppline)->pp_infile, STDIN_FILENO);
	printf("2ok\n");
	if((*ppline)->pp_outfile != STDOUT_FILENO)
	{
		printf("3ok\n");
		dup2((*ppline)->pp_outfile, STDOUT_FILENO);
	}
	printf("4ok\n");
	close_fds(ppline);
}

int	execute_to_builtin(t_ppline *ppline)
{
	// if (check_if_builtin(ppline->pp_first_cmd) == 0)
	// {
	// 	// printf("1aok\n");
	// 	// printf("2aok\n");
	// 	printf (YELS"cmd[%d] infile before dup2: %d\n" RS, i, ppline->pp_infile);
	// 	printf (YELS"cmd[%d] outfile before dup2: %d\n" RS, i, ppline->pp_outfile);
		// close_fds(&ppline);
		printf (MAR"infile after dup2: %d\n" RS, ppline->pp_infile);
		printf (MAR"outfile after dup2: %d\n" RS, ppline->pp_outfile);
		dup_fds(&ppline);
		// close_fds(&ppline);
		ppline->pp_exit = execute_builtin(&ppline);
		// dup2(saved_stdin, STDIN_FILENO);
		// dup2(saved_stdout, STDOUT_FILENO);
		// close(saved_stdin);
		// close(saved_stdout);
		// close(ppline->pp_outfile);
		// return (ppline->pp_exit);
		// exit(0);
		close_fds(&ppline);

	// }
	return (0);
}

int	execute_multi_cmd(t_ppline *ppline)
{
	int	i;
	int	saved_stdin;
	int	saved_stdout;
	int		fd[2];
	char	*line;

// 	// char	*cmd_path;
// 	// cmd_path = NULL;
// 	printf(ORS "EXECUTE KID: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	// printf(GREEN"AFTER dup saved_stdin[%d]\n"RS, saved_stdin);
	// printf(GREEN"AFTER dup saved_stdout[%d]\n"RS, saved_stdout);

	i = 0;
	// print_all_pipeline(ppline);
	init_pipe(&ppline, ppline->ppline_idx);
	// if (num_pipes == 0)
	// 	execute_path_cmd(pp_curr);
	// print_all_pipeline(ppline);
	t_ppline *first = ppline;
	while (i < ppline->ppline_idx)
	{
		if (ppline->ppline_cmd)
		{
			printf("DISPLAY COMMAND execute_multi_cmd\n");
			for (int i = 0; ppline->ppline_cmd[i]; i++)
				printf("%s\n", ppline->ppline_cmd[i]);
			printf("=================\n");
		}
		if (ppline->pp_infile < 0 || ppline->pp_outfile < 0)
		{
			ppline = ppline->next;
			continue ;
		}
		if (ppline->pp_heredoc_status == 1)
		{
			pipe(fd);
			while (1)
			{
				line = readline("> ");

				if (line == NULL || ft_strcmp(ppline->pp_heredoc_eof, line) == 0)
				{
					free(line);
					break;
				}

				ft_putendl_fd(line, fd[1]);
				free(line);
			}

			if (ppline->pp_first_cmd)
			{
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
			}

			close(fd[1]);
		}
		if (ppline->pp_red_status == 1)
		{
			printf(YELLOW"\nbuiltin ppline->pp_red_status == 1\n"RS);
			printf ("after pp_red_status == 1: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			printf ("after pp_red_status == 1: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			if (ppline->pp_fd_out != STDOUT_FILENO)
			{
				printf(R"\ndup2(ppline->pp_fd_out)\n"RS);
				dup2(ppline->pp_fd_out, STDOUT_FILENO);
			}
			if (ppline->pp_fd_in != STDIN_FILENO)
			{
				printf(R"\ndup2(ppline->pp_fd_in)\n"RS);
				dup2(ppline->pp_fd_in, STDIN_FILENO);
			}
			printf(LB"\nafter dup2 before close\n"RS);
			close_red_fds(&ppline);
			printf (GREEN"after pp_red_status == 1: infile: %d\n" RS, ppline->pp_infile);
			printf ("after pp_red_status == 1: outfile: %d\n" RS, ppline->pp_outfile);
			printf ("after pp_red_status == 1: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			printf ("after pp_red_status == 1: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			if (ppline->pp_outfile != ppline->pp_fd_out)
				dup2(ppline->pp_outfile, ppline->pp_fd_out);
			if (ppline->pp_infile != ppline->pp_fd_in)
				dup2(ppline->pp_infile, ppline->pp_fd_in);
			// if (ppline->pp_fd_out != ppline->pp_outfile)
			// 	dup2(ppline->pp_fd_out, ppline->pp_outfile);
			// if (ppline->pp_fd_in != ppline->pp_infile)
			// 	dup2(ppline->pp_fd_in, ppline->pp_infile);	
			printf ("after dup2: infile: %d\n" RS, ppline->pp_infile);
			printf ("after dup2: outfile: %d\n" RS, ppline->pp_outfile);
			printf ("after dup2: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
			printf ("after dup2: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
			close_fds(&ppline);
		}
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
		// 	if (!ppline->pp_first_cmd)
		// 		close(fd[1]);
		// 	// close(fd[0]);
		// 	// printf("HEREDOC FD pp_fd_in after heredoc: %d\n" RS, (ppline)->pp_fd_in);
		// 	// printf("HEREDOC FD pp_fd_out after heredoc: %d\n" RS, (ppline)->pp_fd_out);
		// 	// if (ppline->pp_outfile != ppline->pp_fd_out)
		// 	dup2(ppline->pp_outfile, fd[1]);
		// 	// close(fd[1]);
		// 	// if (ppline->pp_infile != ppline->pp_fd_in)
		// 	// 	dup2(ppline->pp_infile, ppline->pp_fd_in);
		// 	// printf ("HEREDOC after dup2: infile: %d\n" RS, ppline->pp_infile);
		// 	printf ("HEREDOC after dup2: outfile: %d\n" RS, ppline->pp_outfile);
		// 	// printf ("HEREDOC after dup2: pp_fd_in: %d\n" RS, ppline->pp_fd_in);
		// 	// printf ("HEREDOC after dup2: pp_fd_out: %d\n" RS, ppline->pp_fd_out);
		// 	// close_red_fds(&ppline);
		// 	ppline->pp_heredoc_status = 0;
		// }
		if (execute_path_cmd(ppline)) //execute_path_cmd
			msg_error("error executing path_cmd: ", errno);
		// else
		// {
		// 	printf (R "cmd[%d] infile after dup2: %d\n" RS, i, ppline->pp_infile);
		// 	printf ( R"cmd[%d] outfile after dup2: %d\n" RS, i, ppline->pp_outfile);
		// 	// close_fds(&ppline);
		// }
		if (ppline->next)
			ppline = ppline->next;
		i++;
	}
	ppline = first;
	execute_parent(&ppline);
	close(STDOUT_FILENO);
	// printf("BEFORE dup2 saved_stdin[%d]\n", saved_stdin);
	// printf("BEFORE dup2 saved_stdout[%d]\n", saved_stdout);
	close_fds(&ppline);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	// printf("AFTER dup2 saved_stdin[%d]\n", saved_stdin);
	// printf("AFTER saved_stdout[%d]\n", saved_stdout);
	// printf("OUT (%d)\n", saved_stdout);
	// printf("TEST\n");
	close(saved_stdin);
	close(saved_stdout);
	return (EXIT_SUCCESS);
}

void	print_all_pipeline(t_ppline *line)
{
	while(line)
	{
		printf(OR "cmd: %s in: %d out: %d\n" RS, line->ppline_cmd[0], line->pp_infile, line->pp_outfile);
		line = line->next;
	}
}
