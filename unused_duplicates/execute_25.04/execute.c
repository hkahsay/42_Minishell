#include "../../headers/minishell.h"

// void	close_fd(t_ppline *ppline)
// {
// 	// if (ppline->pp_outfile != 1)
// 	// 	close(ppline->pp_outfile);
// 	// if (ppline->pp_infile != 0)
// 	// 	close(ppline->pp_infile);
// }

// static int	fd_close(int *fd)
// {
// 	int	i;

// 	i = 0;
// 	if (*fd != -1)
// 	{
// 		i = close(*fd);
// 		if (i == -1)
// 			error("close", strerror(errno));
// 		*fd = -1;
// 	}
// 	return (i);
// }

// static void	close_all_fd(t_ppline *ppline)
// {
// 	ppline	*pp_curr;

// 	while (ppline)
// 	{
// 		pp_curr = ppline;
// 		close_fd(&pp_curr->pp_pipe[0]);
// 		close_fd(&pp_curr->pp_pipe[1]);
// 		if (pp_curr->pp_id == TOK_REDIR_IN)
// 			close_fd(&ppline->pp_infile);
// 		if (pp_curr->pp_id == TOK_REDIR_OUT)
// 			close_fd(&ppline->pp_outfile);
// 		if (pp_curr->pp_id == TOK_HEREDOC)
// 			close_fd(&ppline->pp_heredoc_fd);
// 		if (pp_curr->pp_id == TOK_APPEND)
// 			close_fd(&ppline->pp_append_fd);
// 		ppline->ppline->next;
// 	}
// }

// void	init_pipe(t_ppline **ppline)
// {
// 	t_ppline *pp_curr;

// 	pp_curr = *ppline;
// 	while (pp_curr)
// 	{
// 		if (pipe(pp_curr->pp_pipe) == -1)
// 			return (-1); //quit prog
// 		pp_curr->pp_pipe[1] = 
// 	}
// }

void	init_pipe(t_ppline **ppline)
{
	t_ppline *pp_curr;

	pp_curr = *ppline;
	pp_curr->pp_outfile = 1;
	while (pp_curr && 1 > pp_curr->ppline_idx)
	{
		if (pipe(pp_curr->pp_pipe) == -1)
			 msg_error("Failed to create pipe", errno);
		pp_curr->pp_outfile = pp_curr->pp_pipe[1];
		pp_curr->pp_infile = pp_curr->pp_pipe[0]; 
		if (pp_curr->next)
			pp_curr = pp_curr->next;
		else
			break ;	
		pp_curr->ppline_idx--;
	}
	if (pp_curr)
		pp_curr->pp_infile = 0;
}

// static int	wait_status(pid_t *pid)
// {
// 	int	status;

// 	*pid = waitpid(-1,  &status, WUNTRACED);
// 	if (WIFSTOPPED(status))
// 		return (WSTOPSIG(status));
// 	if (WIFSIGNALED(g_exit_status))
// 		return (WTERMSIG(status));
// 	if (WIFEXITED(g_exit_status))
// 		return (WEXITSTATUS(status));
// 	assert (0);
// 	return (0);
// }

// static void	init_pid(t_ppline *ppline_cmd, pid_t pid)
// {
// 	while (ppline->ppline_cmd)
// 	{
// 		if (ppline->pp_pid == pid)
// 		{
// 			ppline->pp_pid = -1;
// 			return ;
// 		}
// 	}
// 	assert (0);
// }

// int	wait_execution(t_ppline **ppline_cmd)
// {
// 	int		res;
// 	pid_t	pid;

// 	res = 1;
// 	close_all_redir(&ppline);
// 	while (ppline->ppline_cmd && ppline_idx > 0)
// 	{
// 		// ppline->pp_exit = wait_pid(&ppline->pp_pid);
// 		res = wait_status(&pid);
// 		init_pid(ppline, pid);
// 		ppline_idx--;
// 		if (ppline->next)
// 			ppline->ppline_cmd = ppline->next->ppline_cmd;
// 	}
// 	g_exit_status = res;
// 	// g_exit_status = ppline->pp_exit;
// 	return (g_exit_status);
// }

void execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;
	// long		pid;
	// char		*cmd_path;
	// char		**mini_env_arr;

	// cmd_path = NULL;
	printf(R "EXECUTE: printing cmd_list\n" RS);
	print_cmd_list(cmd);
	// mini_env_arr = ft_mini_env_array(mini_env, ft_mini_env_size(mini_env));
	ppline = build_ppline_array(&cmd, cmd_num, mini_env);
	// echo_ctrl_off();
	// signals_default();

	printf(ORS "EXECUTE: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);
	printf(ORS "EXECUTE: ppline->ppline_cmd[0] %s\n" RS, ppline->ppline_cmd[0]);
	printf(ORS "EXECUTE: ppline->ppline_cmd[1] %s\n\n" RS, ppline->ppline_cmd[1]);
	// pid = fork();
	// if (pid < 0)
	// 	exit_prog(EXIT_FAILURE);
	// if (ppline && ppline->ppline_cmd)
	// {
	if (ppline->ppline_idx == 1 && check_if_builtin(ppline->pp_first_cmd)) //&& ppline->pp_red_status == 0 //&& !ppline->ppline_cmd[1])
	{
		ppline->pp_exit = execute_single_builtin(ppline); //, mini_env_arr, &cmd_path
		return ;
	}	
	// while (ppline->ppline_cmd)
	else
	{
		ppline->pp_exit = execute_multi_cmd(ppline); //, mini_env_arr //return (execute_cmd(mini, &cmd, mini_env));
		// ppline->ppline_cmd = ppline->ppline_cmd->next;
	}
	// wait_execution(&ppline);
	// printf(R "ppline->pp_exit: %d\n" RS, ppline->pp_exit);
	// close_fd(ppline);
	// g_exit_status = ppline->pp_exit;

	// signals_at_start();
	// echo_ctrl_on();
	// return (0);
}
