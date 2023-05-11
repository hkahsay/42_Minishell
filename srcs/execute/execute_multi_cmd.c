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

void execute_parent(t_ppline **ppline)
{
    t_ppline *pp_curr = *ppline;
    int i = 0;


    close_all_fds(ppline);

    while (pp_curr && i < pp_curr->ppline_idx)
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

void	close_red_fds(t_ppline **ppline)
{
	if ((*ppline)->pp_fd_out != -1)
		close((*ppline)->pp_fd_out);
	if ((*ppline)->pp_fd_in != -1)
		close((*ppline)->pp_fd_in);
}


int	execute_to_builtin(t_ppline *ppline)
{
	dup_fds(&ppline);
	ppline->pp_exit = execute_builtin(&ppline);
	close_red_fds(&ppline);
	return (0);
}

int	execute_path_cmd(t_ppline *ppline)
{
	char	*cmd_path;

	cmd_path = NULL;
	ppline->pp_pid = fork();
	if (ppline->pp_pid == 0)
	{
		dup_fds(&ppline);
		if (ppline->pp_red_status == 1)
		{
			if (ppline->pp_fd_out != STDOUT_FILENO)
				dup2(ppline->pp_fd_out, STDOUT_FILENO);
			if (ppline->pp_fd_in != 0)
				dup2(ppline->pp_fd_in, STDIN_FILENO);
		}
		if (check_if_builtin(ppline->pp_first_cmd) == 0)
		{
			close_all_fds(&ppline);
			ppline->pp_exit = execute_builtin(&ppline);
			exit(ppline->pp_exit);
		}
		if (!(search_path(ppline, &cmd_path)))
		{
			ppline->pp_exit = 127;
			g_exit_status = ppline->pp_exit;
			ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
			msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
		}
		close_all_fds(&ppline);
		execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
		msg_error("minishell_VH: error executing command", errno);
	}
	else
	{
		close_red_fds(&ppline);
		close_fds(&ppline);
	}
	return (0);
}

int	execute_multi_cmd(t_ppline *ppline)
{
	int	i;
	// int	saved_stdin;
	// int	saved_stdout;


	ppline->saved_stdin = dup(STDIN_FILENO);
	ppline->saved_stdout = dup(STDOUT_FILENO);
	init_pipe(&ppline, ppline->ppline_idx);
	i = 0;
	t_ppline *first = ppline;
	// print_all_pipeline(ppline);
	while (ppline != NULL && i < ppline->ppline_idx)
	{
		if (ppline->pp_infile < 0 || ppline->pp_outfile < 0)
		{
			ppline = ppline->next;
			continue ;
		}
		if (ppline->pp_heredoc_status == 1)
			execute_heredoc(&ppline);
		if (execute_path_cmd(ppline))
			msg_error("minishell_VH: error executing command", errno);
		// close_fds(&ppline);
		// close_red_fds(&ppline);
		// if (ppline->next != NULL)
		// {
			ppline = ppline->next;

		// }
			i++;
	}
	ppline = first;
	execute_parent(&ppline);
	close(STDOUT_FILENO);
	close_fds(&ppline);
	dup2(ppline->saved_stdout, STDOUT_FILENO);
	dup2(ppline->saved_stdin, STDIN_FILENO);
	close(ppline->saved_stdin);
	close(ppline->saved_stdout);
	return (EXIT_SUCCESS);
}
