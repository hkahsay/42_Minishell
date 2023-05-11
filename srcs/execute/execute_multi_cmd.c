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

void execute_parent(t_ppl **ppl)
{
    t_ppl *pp_curr = *ppl;
    int i = 0;


    close_all_fds(ppl);

    while (pp_curr && i < pp_curr->ppl_idx)
	{
		
        if (pp_curr->pp_pid != 0)
		{
            waitpid(pp_curr->pp_pid, &pp_curr->pp_exit, 0);

            if (WIFSIGNALED(pp_curr->pp_exit)) {
                g_exit_status = WTERMSIG(pp_curr->pp_exit);
            }

            if (WIFEXITED(pp_curr->pp_exit)) {
                g_exit_status = WEXITSTATUS(pp_curr->pp_exit);
            }
        }

        if (pp_curr->next)
		{
            i++;
            pp_curr = pp_curr->next;
        } else
		{
            break;
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

void	close_red_fds(t_ppl **ppl)
{
	if ((*ppl)->pp_fd_out != -1)
		close((*ppl)->pp_fd_out);
	if ((*ppl)->pp_fd_in != -1)
		close((*ppl)->pp_fd_in);
}


int	execute_to_builtin(t_ppl *ppl)
{
	dup_fds(&ppl);
	ppl->pp_exit = execute_builtin(&ppl);
	close_red_fds(&ppl);
	return (0);
}

int	execute_path_cmd(t_ppl *ppl)
{
	char	*cmd_path;

	cmd_path = NULL;
	ppl->pp_pid = fork();
	if (ppl->pp_pid == 0)
	{
		dup_fds(&ppl);
		if (ppl->pp_red_status == 1)
		{
			if (ppl->pp_fd_out != STDOUT_FILENO)
				dup2(ppl->pp_fd_out, STDOUT_FILENO);
			if (ppl->pp_fd_in != 0)
				dup2(ppl->pp_fd_in, STDIN_FILENO);
		}
		if (check_if_builtin(ppl->pp_first_cmd) == 0)
		{
			close_all_fds(&ppl);
			ppl->pp_exit = execute_builtin(&ppl);
			exit(ppl->pp_exit);
		}
		// usleep(50000);
		if (!(search_path(ppl, &cmd_path)))
		{
			ppl->pp_exit = 127;
			g_exit_status = ppl->pp_exit;
			ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
			msg_error(ft_strjoin(ppl->pp_first_cmd, ": command not found"), errno);
		}
		close_all_fds(&ppl);
		execve(cmd_path, (ppl)->ppl_cmd, (ppl)->pp_arr_env);
		msg_error("minishell_VH: error executing command", errno);
	}
	else
	{
		close_red_fds(&ppl);
		close_fds(&ppl);
	}
	return (0);
}

int	execute_multi_cmd(t_ppl *ppl)
{
	int	i;
	// int	saved_stdin;
	// int	saved_stdout;


	ppl->saved_stdin = dup(STDIN_FILENO);
	ppl->saved_stdout = dup(STDOUT_FILENO);
	init_pipe(&ppl, ppl->ppl_idx);
	i = 0;
	t_ppl *first = ppl;
	// print_all_pipeline(ppl);
	while (ppl != NULL && i < ppl->ppl_idx)
	{
		if (ppl->pp_infile < 0 || ppl->pp_outfile < 0)
		{
			ppl = ppl->next;
			continue ;
		}
		if (ppl->pp_heredoc_status == 1)
			execute_heredoc(&ppl);
		if (execute_path_cmd(ppl))
			msg_error("minishell_VH: error executing command", errno);
		// close_fds(&ppl);
		// close_red_fds(&ppl);
		// if (ppl->next != NULL)
		// {
			ppl = ppl->next;

		// }
			i++;
	}
	ppl = first;
	execute_parent(&ppl);
	close(STDOUT_FILENO);
	close_fds(&ppl);
	dup2(ppl->saved_stdout, STDOUT_FILENO);
	dup2(ppl->saved_stdin, STDIN_FILENO);
	close(ppl->saved_stdin);
	close(ppl->saved_stdout);
	return (EXIT_SUCCESS);
}
