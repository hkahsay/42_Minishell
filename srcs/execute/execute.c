#include "../../headers/minishell.h"

void	*init_pipe(t_ppline **ppline) //, int *num_pipes
{
	t_ppline *pp_curr;
	int		fd[2];

	pp_curr = *ppline;
	printf(LBLUE "\nEnter init_pipe OK\n" RS);
	while (pp_curr->next)
	{
		if (pipe(fd) == -1)
			 msg_error("Failed to create pipe", errno);
		// printf(LBLUE "	Init_pipe OK\n" RS);
		if (pp_curr->pp_outfile == 0)
			pp_curr->pp_outfile = fd[1];
		else
			close(fd[1]);
		if (pp_curr->next->pp_infile == 0)
			pp_curr->next->pp_infile = fd[0];
		else
			close(fd[0]);
		// if (pp_curr->next)
		pp_curr = pp_curr->next;
	}
	if (pp_curr->pp_outfile == 0)
		pp_curr->pp_outfile = STDOUT_FILENO;
	// printf(LBLUE "num_pipes: %d\n" RS, *num_pipes);
	printf(LBLUE "Exit init_pipe OK\n\n" RS);
	return (0);
}

int	execute_path_cmd(t_ppline *ppline)
{
	char	*cmd_path;
	pid_t	kid_pid;
	// char	*msg;
// 	int		exit_status;

	cmd_path = NULL;
	printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
	printf(PURPLE "Execute cmd\n" RS);
	kid_pid = fork();
	if (kid_pid == 0)
	{
		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
		{
			g_exit_status = 127;
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
			// printf(R "NO PATH\n" RS);
			// return (-1);
		}
		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
		execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
		msg_error("error execution: ", errno);
		// exit(-1); //EXIT_FAILURE
	}
	else
		waitpid(kid_pid, &(ppline->pp_exit), 0);
	if (WIFEXITED(ppline->pp_exit))	
		ppline->pp_exit = WEXITSTATUS(ppline->pp_exit);
	return (1);	
}

// static void	close_all_fd(t_ppline *ppline)
// {
// 	t_ppline	*pp_curr;

// 	pp_curr = ppline;
// 	while (ppline)
// 	{
// 		if ()
// 		close_fd(&pp_curr->pp_infile[0]);
// 		close_fd(&pp_curr->pp_pipe[1]);
// 		if (pp_curr->pp_id == TOK_REDIR_IN)
// 			close_fd(&ppline->pp_infile);
// 		if (pp_curr->pp_id == TOK_REDIR_OUT)
// 			close_fd(&ppline->pp_outfile);
// 		if (pp_curr->pp_id == TOK_HEREDOC)
// 			close_fd(&ppline->pp_heredoc_fd);
// 		if (pp_curr->pp_id == TOK_REDIR_OUT_APPEND)
// 			close_fd(&ppline->pp_append_fd);
// 		ppline = ppline->next;
// 	}
// }

static void	close_fds(t_ppline **ppline)
{
	t_ppline	*pp_curr;

	pp_curr = *ppline;
	while (pp_curr)
	{
		if (pp_curr->pp_outfile > 2)
			close(pp_curr->pp_outfile);
		if (pp_curr->pp_infile > 2)
			close(pp_curr->pp_infile);
		pp_curr = pp_curr->next;	
	}
}

int	execute_kid(t_ppline *ppline)
{
	printf(YELLOW "Execution kid\n" RS);
	int	stdin_clone;
	int	stdout_clone;

	stdin_clone = dup(STDIN_FILENO);
	stdout_clone = dup(STDOUT_FILENO);
	if (ppline->pp_infile > 2)
		dup2(ppline->pp_infile, STDIN_FILENO);
	if (ppline->pp_outfile > 2)
		dup2(ppline->pp_outfile, STDOUT_FILENO);	
	close_fds(&ppline);
	if (check_if_builtin(ppline->pp_first_cmd) == 0)
	{
		printf(YELLOW "Execution kid builtin_cmd\n" RS);
		ppline->pp_exit = execute_builtin(&ppline); //execute_single_builtin(ppline)
		exit(0);
		return (ppline->pp_exit);
	}
	else
	{
		printf(YELLOW "Execution kid no_builtin path_cmd\n" RS);
		if (!execute_path_cmd(ppline))
			msg_error("error executing path_cmd: ", errno);
	}
	// close_fds(&ppline);
	exit(0);
	return (EXIT_SUCCESS);
}

void	wait_execution(t_ppline **ppline)
{
	// int		res;
	// pid_t	pid;
	t_ppline	*pp_curr;

	// res = 1;
	pp_curr = *ppline;
	close_fds(ppline);
	while (pp_curr)
	{
		waitpid(pp_curr->pp_pid, &(pp_curr->pp_exit), 0);
		pp_curr = pp_curr->next;
	}
}
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

int	execute_multi_cmd(t_ppline *ppline) //, char **mini_env_arr
{
	printf(GGREEN "Execution multi cmd\n" RS);
	t_ppline	*pp_curr;
	// int			num_pipes;
	// pid_t		pp_pid;

	// num_pipes = ppline->ppline_idx - 1;
	pp_curr = ppline;

	// printf(GGREEN "num_pipes: %d\n" RS, num_pipes);
	init_pipe(&pp_curr); //init_pipe(&ppline, &num_pipes);
	printf(GGREEN "Retour after init_pipe Execution multi cmd\n" RS);
	while (pp_curr) // && num_pipes > 0
	{
		printf(GGREEN "Enter while loop multi cmd\n" RS);
		if (pp_curr->pp_infile < 0 || pp_curr->pp_outfile < 0)
		{
			pp_curr = pp_curr->next;
			continue ;
		}
		pp_curr->pp_pid = fork();
		if (pp_curr->pp_pid == -1)
			msg_error("error redir: ", errno);
		if (pp_curr->pp_pid == 0) //child
			execute_kid(pp_curr);	
		pp_curr = pp_curr->next;
	}
	wait_execution(&pp_curr);
	return (EXIT_SUCCESS);
}

void execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;

	printf(GGREEN "EXECUTE: printing cmd_list\n" RS);
	print_cmd_list(cmd);
	ppline = build_ppline_array(&cmd, cmd_num, mini_env);

	printf(ORS "EXECUTE: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);
	printf(ORS "EXECUTE: ppline->ppline_cmd[0] %s\n" RS, ppline->ppline_cmd[0]);
	printf(ORS "EXECUTE: ppline->ppline_cmd[1] %s\n\n" RS, ppline->ppline_cmd[1]);

	//cmd + D is not working, after 2 times yes

	signal(SIGINT, sig_quit_handler);
	signal(SIGQUIT, sig_quit_handler);
	if (ppline->ppline_idx == 1 && ppline->pp_red_status == 0 && check_if_builtin(ppline->pp_first_cmd) == 0)
	{
		printf(R "EXECUTE: execute_single_builtin\n" RS);
		ppline->pp_exit = execute_builtin(&ppline); //have to be assured, if...
		printf(LB "\ng_exit_status: %d\n" RS, g_exit_status);
		return ;
	}
	else
		ppline->pp_exit = execute_multi_cmd(ppline);
	// g_exit_status = ppline->pp_exit;
	// printf(LB "\ng_exit_status: %d\n\n" RS, g_exit_status);
	// // free(ppline->pp_exit);
	// ppline->pp_exit = 0;
}


		// if (pipe(pp_curr->pp_pipe) == -1) //num_pipes > 0 && 
		// 	msg_error("error redir: ", errno);
		// pp_pid = fork();
		// if (pp_pid == -1)
		// 	msg_error("error redir: ", errno);
		// else if (pp_pid == 0) //child
		// {
		// 	dup2(pp_curr->pp_pipe[0], STDIN_FILENO);
		// 	close(pp_curr->pp_pipe[0]);
		// 	close(pp_curr->pp_pipe[1]);
		// 	if (execute_pipe_cmd(ppline) == -1)
		// 		msg_error("execution pipe_cmd: ", errno);
		// }
		// else //parent
		// {
		// 	close(pp_curr->pp_pipe[0]);

		// 	if (waitpid(pp_pid, &pp_curr->pp_exit, 0) == -1)
		// 		msg_error("waitpid: ", errno);
		// 	if (WIFEXITED(pp_curr->pp_exit))
		// 		pp_curr->pp_exit = WEXITSTATUS(pp_curr->pp_exit);
		// }
		// if (pp_curr->next)
	
		// num_pipes++;
	// }
// 	printf("PP_outfile: %d\n", (pp_curr)->pp_outfile);
// 	printf("PP_infile: %d\n", (pp_curr)->pp_infile);
// 	// init_pipe(&ppline, &num_pipes);
// 	printf(GGREEN "NUMBER pipes returned: %d\n" RS, num_pipes);