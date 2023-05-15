#include "../../headers/minishell.h"

static void	error_path_cmd(t_ppl *ppl)
{
	ppl->pp_exit = 127;
	g_exit_status = ppl->pp_exit;
	ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
	msg_error(ft_strjoin(ppl->pp_first_cmd, ": command not found"), errno);
	exit(0);
}

void	execute_parent(t_ppl **ppl)
{
	t_ppl	*pp_curr;
	int		i;

	i = 0;
	pp_curr = *ppl;
	close_all_fds(ppl);
	while (pp_curr && i < pp_curr->ppl_idx)
	{
		if (pp_curr->pp_pid != 0)
		{
			waitpid(pp_curr->pp_pid, &pp_curr->pp_exit, 0);
			if (WIFSIGNALED(pp_curr->pp_exit))
				g_exit_status = WTERMSIG(pp_curr->pp_exit);
			if (WIFEXITED(pp_curr->pp_exit))
				g_exit_status = WEXITSTATUS(pp_curr->pp_exit);
		}
		if (pp_curr->next)
		{
			i++;
			pp_curr = pp_curr->next;
		}
		else
			break ;
	}
}

int	execute_to_builtin(t_ppl *ppl)
{
	dup_fds(&ppl);
	ppl->pp_exit = execute_builtin(&ppl);
	close_red_fds(&ppl);
	return (0);
}

int	execute_fork_cmd(t_ppl *ppl)
{
	char	*cmd_path;

	signal(SIGINT, SIG_IGN);
	cmd_path = NULL;
	ppl->pp_pid = fork();
	if (ppl->pp_pid == 0)
	{
		signals_default();
		manage_dup(&ppl);
		if (check_if_builtin(ppl->pp_first_cmd) == 0)
		{
			close_all_fds(&ppl);
			ppl->pp_exit = execute_builtin(&ppl);
			exit(ppl->pp_exit);
		}
		if (!(search_path(ppl, &cmd_path)))
			error_path_cmd(ppl);
		close_all_fds(&ppl);
		execve(cmd_path, (ppl)->ppl_cmd, (ppl)->pp_arr_env);
		msg_error("minishell_VH: error executing command", errno);
	}
	else
		finish_exec(&ppl);
	return (0);
}

int	execute_pipe_cmd(t_ppl *ppl)
{
	int		i;
	t_ppl	*first;

	i = 0;
	first = ppl;
	dup_saved_stds(&ppl);
	init_pipe(&ppl, ppl->ppl_idx);
	while (ppl != NULL && i < ppl->ppl_idx)
	{
		if (ppl->pp_infile < 0 || ppl->pp_outfile < 0)
		{
			ppl = ppl->next;
			continue ;
		}
		if (ppl->pp_heredoc_status == 1)
			execute_heredoc(&ppl);
		if (execute_fork_cmd(ppl))
			msg_error("minishell_VH: error executing command", errno);
		if (ppl->pp_heredoc_status == 1)
		{
			dup2((ppl)->saved_stdin, STDIN_FILENO);
			close((ppl)->saved_stdin);
		}	
		ppl = ppl->next;
		i++;
	}
	ppl = first;
	finish_multi_exec(&ppl);
	return (EXIT_SUCCESS);
}
