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
	if (*ppline)
	{
		if ((*ppline)->pp_outfile != STDOUT_FILENO)
			close((*ppline)->pp_outfile);
		if ((*ppline)->pp_infile != STDIN_FILENO)
			close((*ppline)->pp_infile);
	}
}

void	close_red_fds(t_ppline **ppline)
{
	// if ((*ppline)->pp_fd_out != STDOUT_FILENO)
	// 	close((*ppline)->pp_fd_out);
	// if ((*ppline)->pp_fd_in != STDIN_FILENO)
	// 	close((*ppline)->pp_fd_in);
	if ((*ppline)->pp_fd_out != STDOUT_FILENO && (*ppline)->pp_fd_out != (*ppline)->pp_outfile)
        close((*ppline)->pp_fd_out);
    if ((*ppline)->pp_fd_in != STDIN_FILENO && (*ppline)->pp_fd_in != (*ppline)->pp_infile)
        close((*ppline)->pp_fd_in);
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
		// printf(LB"PPCURR: %d\n" RS, pp_curr->pp_pid);
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
			// printf(LB"Break\n"RS);
			break ;
		}
	}
}

void	dup_fds(t_ppline **ppline)
{
	// printf("1ok\n");
	if((*ppline)->pp_infile != STDIN_FILENO)
		dup2((*ppline)->pp_infile, STDIN_FILENO);
	// printf("2ok\n");
	if((*ppline)->pp_outfile != STDOUT_FILENO)
	{
		// printf("3ok\n");
		dup2((*ppline)->pp_outfile, STDOUT_FILENO);
	}
	// printf("4ok\n");
	close_fds(ppline);
}

int	execute_path_cmd(t_ppline *ppline)
{
	char	*cmd_path;
	// t_cmd	*cmd;

	cmd_path = NULL;
	ppline->pp_pid = fork();
	if (ppline->pp_pid == 0)
	{
		if (check_if_builtin(ppline->pp_first_cmd) == 0)
		{
			if (ppline->pp_outfile != STDOUT_FILENO)
				dup2(ppline->pp_outfile, STDOUT_FILENO);
			if (ppline->pp_infile != STDIN_FILENO)
				dup2(ppline->pp_infile, STDIN_FILENO);
			close_all_fds(&ppline);
			if (ppline->pp_outfile != ppline->pp_fd_out)
				close(ppline->pp_fd_out);
            close_red_fds(&ppline);
            // close_all_fds(&ppline);
			ppline->pp_exit = execute_builtin(&ppline);
			// lose_all_fds(&ppline);
			exit(ppline->pp_exit);
		}
		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
		{
			ppline->pp_exit = 127;
			// ft_putnbr_fd(ppline->pp_exit, STDERR_FILENO);
			g_exit_status = ppline->pp_exit;
			// ft_putnbr_fd(g_exit_status, STDERR_FILENO);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
		}
		if (ppline->pp_outfile != STDOUT_FILENO)
			dup2(ppline->pp_outfile, STDOUT_FILENO);
		if (ppline->pp_infile != STDIN_FILENO)
			dup2(ppline->pp_infile, STDIN_FILENO);
		close_red_fds(&ppline);
		close_all_fds(&ppline);
		execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
		// if (execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env) == -1)
			msg_error("error execution: ", errno);
	}
	else
		close_fds(&ppline);
	return (0);
}

int	execute_to_builtin(t_ppline *ppline)
{
		dup_fds(&ppline);
		ppline->pp_exit = execute_builtin(&ppline);
		close_fds(&ppline);
	return (0);
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
	while ((*ppline)->next && i < ppline_idx)
	{
		if (pipe(pipes) == -1)
			 msg_error("Failed to create pipe", errno);
		(*ppline)->pp_outfile = pipes[1];
		(*ppline)->next->pp_infile = pipes[0];
		// (*ppline)->pp_fd_out = pipes[1];
		// (*ppline)->next->pp_fd_in = pipes[0];
		*ppline = (*ppline)->next;
		i++;
	}
	*ppline = first;
	return (0);
}

int	execute_multi_cmd(t_ppline *ppline)
{
	int	i;
	int	saved_stdin;
	int	saved_stdout;
	int		fd[2];
	char	*line;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	init_pipe(&ppline, ppline->ppline_idx);
	i = 0;
	t_ppline *first = ppline;
	while (i < ppline->ppline_idx)
	{
		// if (ppline->ppline_cmd)
		// {
		// 	printf("DISPLAY COMMAND execute_multi_cmd\n");
		// 	for (int i = 0; ppline->ppline_cmd[i]; i++)
		// 		printf("%s\n", ppline->ppline_cmd[i]);
		// 	printf("=================\n");
		// }
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
			if (ppline->pp_fd_out != STDOUT_FILENO)
			{
				dup2(ppline->pp_fd_out, STDOUT_FILENO);
			}
			if (ppline->pp_fd_in != STDIN_FILENO)
			{
				dup2(ppline->pp_fd_in, STDIN_FILENO);
			}
			// close_red_fds(&ppline);
			// if (ppline->pp_outfile != ppline->pp_fd_out)
				close(ppline->pp_fd_out);
				close(STDOUT_FILENO);
				dup2(saved_stdout, STDOUT_FILENO);
				// close(STDIN_FILENO);
				// dup2(saved_stdin, STDIN_FILENO);

			// 	dup2(ppline->pp_outfile, ppline->pp_fd_out);
			// if (ppline->pp_infile != ppline->pp_fd_in)
				close(ppline->pp_fd_in);
			// 	dup2(ppline->pp_infile, ppline->pp_fd_in);
			// close_fds(&ppline);
		}
		if (execute_path_cmd(ppline)) //execute_path_cmd
			msg_error("error executing path_cmd: ", errno);
		if (ppline->next)
			ppline = ppline->next;
		i++;
	}
	ppline = first;
	execute_parent(&ppline);
	close(STDOUT_FILENO);
	close_fds(&ppline);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
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

