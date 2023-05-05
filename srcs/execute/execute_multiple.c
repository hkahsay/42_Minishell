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
	printf ("infile: %d\n" RS, (*ppline)->pp_infile);
	printf (" outfile: %d\n" RS, (*ppline)->pp_outfile);
	if((*ppline)->pp_infile != STDIN_FILENO)
		dup2((*ppline)->pp_infile, STDIN_FILENO);
	printf("2ok\n");
	if((*ppline)->pp_outfile != STDOUT_FILENO)
	{
		printf("3ok\n");
		dup2((*ppline)->pp_outfile, STDOUT_FILENO);
		printf ("infile: %d\n" RS, (*ppline)->pp_infile);
		printf ("outfile: %d\n" RS, (*ppline)->pp_outfile);
	}
	printf("4ok\n");
	printf ("infile: %d\n" RS, (*ppline)->pp_infile);
	printf ("outfile: %d\n" RS, (*ppline)->pp_outfile);
	close_fds(ppline);
	printf ("infile: %d\n" RS, (*ppline)->pp_infile);
	printf ("outfile: %d\n" RS, (*ppline)->pp_outfile);
}

int	execute_multi_cmd(t_ppline *ppline)
{
	int	i;
	int	saved_stdin;
	int	saved_stdout;
// 	// char	*cmd_path;
// 	// cmd_path = NULL;
// 	printf(ORS "EXECUTE KID: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);

	i = 0;
	// print_all_pipeline(ppline);
	init_pipe(&ppline, ppline->ppline_idx);
	// if (num_pipes == 0)
	// 	execute_path_cmd(pp_curr);
	// print_all_pipeline(ppline);
	t_ppline *first = ppline;
	while (i < ppline->ppline_idx)
	{
		printf("DISPLAY COMMAND\n");
		for (int i = 0; ppline->ppline_cmd[i]; i++)
			printf("%s\n", ppline->ppline_cmd[i]);
		printf("=================\n");
		// printf ("cmds[%d] infile: %d\n" RS, i, ppline->pp_infile);
		// printf ("cmd[%d] outfile: %d\n" RS, i, ppline->pp_outfile);
		// dup_fds(&ppline);
		// close_fds(&first);
		if (ppline->pp_infile < 0 || ppline->pp_outfile < 0)
		{
			ppline = ppline->next;
			continue ;
		}
		if (check_if_builtin(ppline->pp_first_cmd) == 0)
		{
			if (check_if_builtin(ppline->pp_first_cmd) == 0)
			{
				// printf("1aok\n");
				// printf("2aok\n");
				printf (YELS"cmd[%d] infile after dup2: %d\n" RS, i, ppline->pp_infile);
				printf (YELS"cmd[%d] outfile after dup2: %d\n" RS, i, ppline->pp_outfile);
				// close_fds(&ppline);
				dup_fds(&ppline);
				// close_fds(&ppline);

				ppline->pp_exit = execute_builtin(&ppline);
				// close_fds(&ppline);
				printf (MAR"cmd[%d] infile after dup2: %d\n" RS, i, ppline->pp_infile);
				printf (MAR"cmd[%d] outfile after dup2: %d\n" RS, i, ppline->pp_outfile);
				// dup2(saved_stdin, STDIN_FILENO);
				// dup2(saved_stdout, STDOUT_FILENO);
				// close(saved_stdin);
				// close(saved_stdout);
				// return (ppline->pp_exit);
				// exit(0);
				// close_fds(&ppline);

			}
			// else
			// 	close_fds(&ppline);

		}
		else
		{
			// printf("BEFORE EXECUTION\n");
			
			if (execute_path_cmd(ppline)) //execute_path_cmd
				msg_error("error executing path_cmd: ", errno);
			else
			{
				printf (R "cmd[%d] infile after dup2: %d\n" RS, i, ppline->pp_infile);
				printf ( R"cmd[%d] outfile after dup2: %d\n" RS, i, ppline->pp_outfile);
				// close_fds(&ppline);
			}

		}
		if (ppline->next)
			ppline = ppline->next;
		i++;
	}
	ppline = first;
	execute_parent(&ppline);
	close(STDOUT_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	ft_putstr_fd("Hello\n", saved_stdout);
	printf("OUT (%d)\n", saved_stdout);
	printf("TEST\n");
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
