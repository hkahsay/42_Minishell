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

// int	command_not_found(t_cmd *curr, char **envp)
// {
// 	if (execve(curr->tab[0], curr->tab, envp) == -1)
// 	{
// 		printf("command not found\n");
// 		g_exit_status = 127;
// 		return (-1);
// 	}
// 	return (0);
// }


static void	wait_child(t_ppline *ppline)
{
	printf(LIME "Wait child\n" RS);
	t_ppline	*pp_curr;
	int			exit_status;

	pp_curr = ppline;
	while (pp_curr)
	{
		if (pp_curr->pp_pid > 0)
		{
			waitpid(pp_curr->pp_pid, &exit_status, 0);
			if (WIFEXITED(exit_status))
				pp_curr->pp_exit = WEXITSTATUS(exit_status);
		}
		pp_curr = pp_curr->next;
	}
	g_exit_status = pp_curr->pp_exit;
}

void	init_pipe(t_ppline **ppline)
{
	t_ppline *pp_curr;

	pp_curr = *ppline;
	pp_curr->pp_outfile = STDOUT_FILENO;
	printf(LBLUE "\nEnter init_pipe OK\n" RS);
	while (pp_curr && 1 > pp_curr->ppline_idx)
	{
		if (pipe(pp_curr->pp_pipe) == -1)
			 msg_error("Failed to create pipe", errno);
		printf(LBLUE "	Init_pipe OK\n" RS);
		pp_curr->pp_pipe[0] = STDIN_FILENO;
		pp_curr->pp_pipe[1] = STDOUT_FILENO;
		if (pp_curr->next)
			pp_curr = pp_curr->next;
		else
			break ;
		pp_curr->ppline_idx--;
	}
	if (pp_curr)
		pp_curr->pp_infile = STDIN_FILENO;
	printf(LBLUE "Exit init_pipe OK\n\n" RS);
}

// static void	close_pipe(t_ppline *ppline)
// {
// 	printf(LIME "Close pipe\n" RS);
// 	t_ppline	*pp_curr;

// 	pp_curr = ppline;
// 	while (pp_curr)
// 	{
// 		if (pp_curr->pp_pipe[0] > 2)
// 			close(pp_curr->pp_pipe[0]);
// 		if (pp_curr->pp_pipe[1] > 2)
// 			close(pp_curr->pp_pipe[1]);
// 		if (pp_curr->next)
// 			pp_curr = pp_curr->next;
// 		else
// 			break ;
// 	}
// }

static int	execute_cmd(t_ppline *ppline)
{
	char	*cmd_path;
	// char	*msg;
// 	int		exit_status;

	cmd_path = NULL;
	printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
	printf(PURPLE "Execute cmd\n" RS);
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
	exit(-1); //EXIT_FAILURE
}


int	execute_multi_cmd(t_ppline *ppline) //, char **mini_env_arr
{
	printf(GGREEN "Execution multi cmd\n" RS);
	t_ppline	*pp_curr;
// 	char	*cmd_path;
// // 	int		exit_status;

// 	cmd_path = NULL;
	pp_curr = ppline;
	init_pipe(&ppline);
	printf("PP_infile: %d\n", (pp_curr)->pp_infile);
	printf("PP_outfile: %d\n", (pp_curr)->pp_outfile);
	printf("PP_pipe[0]: %d\n", (pp_curr)->pp_pipe[0]);
	printf("PP_pipe[1]: %d\n", (pp_curr)->pp_pipe[1]);
	while (pp_curr)
	{
		printf("PP_pipe[0] in the loop: %d\n", (pp_curr)->pp_pipe[0]);
		printf("PP_pipe[1] in the loop: %d\n", (pp_curr)->pp_pipe[1]);
		pp_curr->pp_pid = fork();
		if (pp_curr->pp_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pp_curr->pp_pid == 0)
		{
			// printf("PP_pipe[0] in the loop: %d\n", (pp_curr)->pp_pipe[0]);
			// printf("PP_pipe[1] in the loop: %d\n", (pp_curr)->pp_pipe[1]);
			dup2(pp_curr->pp_pipe[1], STDOUT_FILENO);
			close(pp_curr->pp_pipe[1]);
			printf("PP_pipe[0] close(pp_curr->pp_pipe[1]): %d\n", (pp_curr)->pp_pipe[0]);
			printf("PP_pipe[1] close(pp_curr->pp_pipe[1]): %d\n", (pp_curr)->pp_pipe[1]);
			dup2(pp_curr->pp_pipe[0], STDIN_FILENO);
			printf("PP_pipe[0] dup2(pp_curr->pp_pipe[0], STDIN_FILENO): %d\n", (pp_curr)->pp_pipe[0]);
			printf("PP_pipe[1] dup2(pp_curr->pp_pipe[0], STDIN_FILENO): %d\n", (pp_curr)->pp_pipe[1]);
			close(pp_curr->pp_pipe[0]);
			printf("PP_pipe[0] close(pp_curr->pp_pipe[0]): %d\n", (pp_curr)->pp_pipe[0]);
			printf("PP_pipe[1] close(pp_curr->pp_pipe[0]): %d\n", (pp_curr)->pp_pipe[1]);
			// if (pp_curr->pp_infile > 2)
			// {
			// 	dup2(pp_curr->pp_infile, STDIN_FILENO);
			// 	printf("PP_infile after dup2: %d\n", (pp_curr)->pp_infile);
			// }
			// if (pp_curr->pp_pipe[1] > 2)
			// {
			// 	dup2(pp_curr->pp_outfile, STDOUT_FILENO);
			// 	printf("PP_outfile after dup2: %d\n", (pp_curr)->pp_outfile);
			// }
			// close_pipe(ppline);
			if (execute_builtin(&ppline) == 1) //->ppline_cmd[0], ppline->pp_list_env
			{
				printf(GGREEN "\nExecution multi cmd no builtin\n\n" RS);
				execute_cmd(ppline);
			}
		}
		else
		{
			close(pp_curr->pp_pipe[0]);
			char *heredoc_text = readline("heredoc> ");
			write(ppline->pp_pipe[1], heredoc_text, ft_strlen(heredoc_text));
			my_free(heredoc_text);
			close(ppline->pp_pipe[1]);
		}
		if (pp_curr->next)
			pp_curr = pp_curr->next;
		else
			break ;
	}
	// close_pipe(ppline);
	wait_child(ppline);
	return (0);
}

int	execute_single_builtin(t_ppline *ppline) //, char **mini_env_arr, char **cmd_path
{
	int		exit_status;

	exit_status = 0;

	printf(YELLOW "Execution single_builtin\n" RS);
	printf(YELLOW "pp_red_status: %d\n" RS, ppline->pp_red_status);

	exit_status = execute_builtin(&ppline);
	printf(R "exit_status: %d\n" RS, exit_status);
	return (exit_status);
}

void execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;

	printf(R "EXECUTE: printing cmd_list\n" RS);
	print_cmd_list(cmd);
	ppline = build_ppline_array(&cmd, cmd_num, mini_env);

	printf(ORS "EXECUTE: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);
	printf(ORS "EXECUTE: ppline->ppline_cmd[0] %s\n" RS, ppline->ppline_cmd[0]);
	printf(ORS "EXECUTE: ppline->ppline_cmd[1] %s\n\n" RS, ppline->ppline_cmd[1]);

	//cmd + D is not working, after 2 times yes

	signal(SIGINT, sig_quit_handler);
	signal(SIGQUIT, sig_quit_handler);
	if (ppline->ppline_idx == 1 && check_if_builtin(ppline->pp_first_cmd))
	{
		ppline->pp_exit = execute_single_builtin(ppline);
		return ;
	}
	else
		ppline->pp_exit = execute_multi_cmd(ppline);
}


	// wait_execution(&ppline);
	// printf(R "ppline->pp_exit: %d\n" RS, ppline->pp_exit);
	// close_fd(ppline);
	// g_exit_status = ppline->pp_exit;

	// signals_at_start();
	// echo_ctrl_on();
	// return (0);
