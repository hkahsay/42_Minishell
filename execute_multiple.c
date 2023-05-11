#include "../../headers/minishell.h"
void	close_all_fds(t_ppl **ppl)
{
	t_ppl	*pp_curr;

	pp_curr = *ppl;
	while (pp_curr)
	{
		if (pp_curr->pp_infile != STDIN_FILENO)
			close(pp_curr->pp_infile);
		if (pp_curr->pp_outfile != STDOUT_FILENO)
			close(pp_curr->pp_outfile);
		pp_curr = pp_curr->next;
	}
}

void	close_fds(t_ppl **ppl)
{
	if (*ppl)
	{
		if ((*ppl)->pp_outfile != STDOUT_FILENO)
			close((*ppl)->pp_outfile);
		if ((*ppl)->pp_infile != STDIN_FILENO)
			close((*ppl)->pp_infile);
	}
}

void	close_red_fds(t_ppl **ppl)
{
	// if ((*ppl)->pp_fd_out != STDOUT_FILENO)
	// 	close((*ppl)->pp_fd_out);
	// if ((*ppl)->pp_fd_in != STDIN_FILENO)
	// 	close((*ppl)->pp_fd_in);
	if ((*ppl)->pp_fd_out != STDOUT_FILENO && (*ppl)->pp_fd_out != (*ppl)->pp_outfile)
        close((*ppl)->pp_fd_out);
    if ((*ppl)->pp_fd_in != STDIN_FILENO && (*ppl)->pp_fd_in != (*ppl)->pp_infile)
        close((*ppl)->pp_fd_in);
}

void	execute_parent(t_ppl **ppl)
{
	t_ppl	*pp_curr;
	int			i;

	i = 0;
	pp_curr = *ppl;
	close_all_fds(ppl);
	while (pp_curr && i < pp_curr->ppl_idx)
	{
		// waitpid(pp_curr->pp_pid, &(pp_curr->pp_exit), 0);
		// printf(LB"PPCURR: %d\n" RS, pp_curr->pp_pid);
		if (pp_curr->pp_pid != 0)
		{
			waitpid(pp_curr->pp_pid, &pp_curr->pp_exit, 0);
			int signal_number = WTERMSIG(pp_curr->pp_exit);
    			printf("Child process terminated by signal: %d\n", signal_number);
			// if (WIFSIGNALED(pp_curr->pp_exit))
				// g_exit_status = pp_curr->pp_exit;
				g_exit_status = signal_number;
			if (WIFEXITED(pp_curr->pp_exit))
				g_exit_status = WEXITSTATUS(pp_curr->pp_exit);
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

void	dup_fds(t_ppl **ppl)
{
	// printf("1ok\n");
	if((*ppl)->pp_infile != STDIN_FILENO)
		dup2((*ppl)->pp_infile, STDIN_FILENO);
	// printf("2ok\n");
	if((*ppl)->pp_outfile != STDOUT_FILENO)
	{
		// printf("3ok\n");
		dup2((*ppl)->pp_outfile, STDOUT_FILENO);
	}
	// printf("4ok\n");
	close_fds(ppl);
}

int	execute_path_cmd(t_ppl *ppl)
{
	char	*cmd_path;
	// t_cmd	*cmd;

	cmd_path = NULL;
	ppl->pp_pid = fork();
	if (ppl->pp_pid == 0)
	{
		if (check_if_builtin(ppl->pp_first_cmd) == 0)
		{
			if (ppl->pp_outfile != STDOUT_FILENO)
				dup2(ppl->pp_outfile, STDOUT_FILENO);
			if (ppl->pp_infile != STDIN_FILENO)
				dup2(ppl->pp_infile, STDIN_FILENO);
			close_all_fds(&ppl);
			if (ppl->pp_outfile != ppl->pp_fd_out)
				close(ppl->pp_fd_out);
            close_red_fds(&ppl);
            // close_all_fds(&ppl);
			ppl->pp_exit = execute_builtin(&ppl);
			// lose_all_fds(&ppl);
			exit(ppl->pp_exit);
		}
		if (!(search_path(ppl, &cmd_path))) //, mini_env_arr //
		{
			ppl->pp_exit = 127;
			// ft_putnbr_fd(ppl->pp_exit, STDERR_FILENO);
			g_exit_status = ppl->pp_exit;
			// ft_putnbr_fd(g_exit_status, STDERR_FILENO);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			msg_error(ft_strjoin(ppl->pp_first_cmd, ": command not found"), errno);
		}
		if (ppl->pp_outfile != STDOUT_FILENO)
			dup2(ppl->pp_outfile, STDOUT_FILENO);
		if (ppl->pp_infile != STDIN_FILENO)
			dup2(ppl->pp_infile, STDIN_FILENO);
		close_red_fds(&ppl);
		close_all_fds(&ppl);
		execve(cmd_path, (ppl)->ppl_cmd, (ppl)->pp_arr_env);
		// if (execve(cmd_path, (ppl)->ppl_cmd, (ppl)->pp_arr_env) == -1)
			msg_error("error execution: ", errno);
	}
	else
		close_fds(&ppl);
	return (0);
}

int	execute_to_builtin(t_ppl *ppl)
{
		dup_fds(&ppl);
		ppl->pp_exit = execute_builtin(&ppl);
		close_fds(&ppl);
	return (0);
}

static void	*init_pipe(t_ppl **ppl, int ppl_idx) //, int *num_pipes
{
	int		pipes[2];
	int		i;

	t_ppl *first;
	first = *ppl;
	i = 0;
	if (ppl_idx == 1)
	 	return (0);
	while ((*ppl)->next && i < ppl_idx)
	{
		if (pipe(pipes) == -1)
			 msg_error("Failed to create pipe", errno);
		(*ppl)->pp_outfile = pipes[1];
		(*ppl)->next->pp_infile = pipes[0];
		// (*ppl)->pp_fd_out = pipes[1];
		// (*ppl)->next->pp_fd_in = pipes[0];
		*ppl = (*ppl)->next;
		i++;
	}
	*ppl = first;
	return (0);
}

int	execute_multi_cmd(t_ppl *ppl)
{
	int	i;
	int	saved_stdin;
	int	saved_stdout;
	int		fd[2];
	char	*line;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	init_pipe(&ppl, ppl->ppl_idx);
	i = 0;
	t_ppl *first = ppl;
	while (i < ppl->ppl_idx)
	{
		// if (ppl->ppl_cmd)
		// {
		// 	printf("DISPLAY COMMAND execute_multi_cmd\n");
		// 	for (int i = 0; ppl->ppl_cmd[i]; i++)
		// 		printf("%s\n", ppl->ppl_cmd[i]);
		// 	printf("=================\n");
		// }
		if (ppl->pp_infile < 0 || ppl->pp_outfile < 0)
		{
			ppl = ppl->next;
			continue ;
		}
		
		if (ppl->pp_heredoc_status == 1)
		{
			pipe(fd);
			while (1)
			{
				line = readline("> ");

				if (line == NULL || ft_strcmp(ppl->pp_heredoc_eof, line) == 0)
				{
					my_free(line);
					break;
				}

				ft_putendl_fd(line, fd[1]);
				my_free(line);
			}

			if (ppl->pp_first_cmd)
			{
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
			}

			close(fd[1]);
		}
		if (ppl->pp_red_status == 1)
		{
			if (ppl->pp_fd_out != STDOUT_FILENO)
			{
				dup2(ppl->pp_fd_out, STDOUT_FILENO);
			}
			if (ppl->pp_fd_in != STDIN_FILENO)
			{
				dup2(ppl->pp_fd_in, STDIN_FILENO);
			}
			// close_red_fds(&ppl);
			// if (ppl->pp_outfile != ppl->pp_fd_out)
				close(ppl->pp_fd_out);
				close(STDOUT_FILENO);
				dup2(saved_stdout, STDOUT_FILENO);
				// close(STDIN_FILENO);
				// dup2(saved_stdin, STDIN_FILENO);

			// 	dup2(ppl->pp_outfile, ppl->pp_fd_out);
			// if (ppl->pp_infile != ppl->pp_fd_in)
				close(ppl->pp_fd_in);
			// 	dup2(ppl->pp_infile, ppl->pp_fd_in);
			// close_fds(&ppl);
		}
		if (execute_path_cmd(ppl)) //execute_path_cmd
			msg_error("error executing path_cmd: ", errno);
		if (ppl->next)
			ppl = ppl->next;
		i++;
	}
	ppl = first;
	execute_parent(&ppl);
	close(STDOUT_FILENO);
	close_fds(&ppl);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (EXIT_SUCCESS);
}

void	print_all_pipeline(t_ppl *line)
{
	while(line)
	{
		printf(OR "cmd: %s in: %d out: %d\n" RS, line->ppl_cmd[0], line->pp_infile, line->pp_outfile);
		line = line->next;
	}
}

