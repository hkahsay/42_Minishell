#include "../../headers/minishell.h"

// void	wait_status(t_ppline *ppline)
// {
// 	while(ppline)
// 	{
// 		if (ppline->pp_pid != 0)
// 		{
// 			waitpid(ppline->pp_pid, &g_exit_status, 0);
// 			if (WIFSIGNALED(g_exit_status))
// 				g_exit_status = 128 + g_exit_status;
// 			if (WIFEXITED(g_exit_status))
// 				g_exit_status = WEXITSTATUS(g_exit_status);	
// 		}
// 		if (ppline->next)
// 			ppline = ppline->next;
// 		else
// 			break;	
// 	}
// }

// static int	execute_builtin_redir(t_ppline *ppline)
// {
// 	printf(ORS "Execution builtin_red\n" RS);
// 	printf("CMD: %s\n", (ppline)->pp_first_cmd);
// 	// if //(red_ptr->id == TOK_REDIR_OUT)
// 	printf("PP_outfile: %d\n", (ppline)->pp_outfile);
// 	printf("PP_infile: %d\n", (ppline)->pp_infile);
// 	if (check_if_builtin(ppline->pp_first_cmd))
// 	{
// 		printf("Builtin\n");
// 		if ((ppline)->pp_outfile > 1)
// 		{
// 			dup2((ppline)->pp_outfile, STDOUT_FILENO);
// 			close((ppline)->pp_outfile);
// 			printf("PP_outfile closed\n");
// 			printf("PP_outfile: %d\n", (ppline)->pp_outfile);
// 		}
// 		if ((ppline)->pp_infile > 1)
// 		{
// 			dup2((ppline)->pp_infile, STDIN_FILENO);
// 			close((ppline)->pp_infile);
// 			printf("PP_infile closed\n");
// 			printf("PP_infile: %d\n", (ppline)->pp_infile);
// 		}
// 		execute_builtin(&ppline); //->ppline_cmd[0], ppline->pp_list_env
// 		// dup2((ppline)->pp_outfile, STDOUT_FILENO);
// 		// close((ppline)->pp_outfile);
// 	}
// 	return (0);
// }

// static int	execute_single_red(t_ppline *ppline, char *cmd_path) //
// {
// 	(void)cmd_path;
// 	int 	pid;
// 	int		exit_status;

// 	// cmd_path = NULL;
// 	// (void)ppline;
// 	if ((check_if_builtin(ppline->pp_first_cmd) == 2))
// 	{
// 		close_fd(ppline);

// 	}
// 	printf(GGREEN "Execution single_red\n" RS);
// 	printf("CMD: %s\n", (ppline)->pp_first_cmd);
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("Error fork");
// 		return (0);
// 	}
// 	if (pid == 0)
// 	{
// 		if (execute_builtin_redir(ppline))
// 			g_exit_status = 1;
// 		exit (g_exit_status);
// 	}
// 	else
// 	{
// 		waitpid(pid, &exit_status, 0);
// 		wait_status(ppline);
// 	}
// 	close_fd(ppline);
	// if //(red_ptr->id == TOK_REDIR_OUT)
	// printf("PP_outfile: %d\n", (ppline)->pp_outfile);
	// printf("PP_infile: %d\n", (ppline)->pp_infile);
	// if (check_if_builtin(ppline->pp_first_cmd))
	// {
	// 	printf("Builtin\n");
	// 	if ((ppline)->pp_outfile > 1)
	// 	{
	// 		dup2((ppline)->pp_outfile, STDOUT_FILENO);
	// 		close((ppline)->pp_outfile);
	// 		printf("PP_outfile closed\n");
	// 		printf("PP_outfile: %d\n", (ppline)->pp_outfile);
	// 	}
	// 	if ((ppline)->pp_infile > 1)
	// 	{
	// 		dup2((ppline)->pp_infile, STDIN_FILENO);
	// 		close((ppline)->pp_infile);
	// 		printf("PP_infile closed\n");
	// 		printf("PP_infile: %d\n", (ppline)->pp_infile);
	// 	}
	// 	is_builtin(&ppline->ppline_cmd[0], ppline->pp_list_env);
	// 	// dup2((ppline)->pp_outfile, STDOUT_FILENO);
	// 	// close((ppline)->pp_outfile);
	// }

	// else
	// {
	// 	printf("NOT builtin\n");
	// 	if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
	// 	{
	// 		printf("NO PATH\n");
	// 		return (-1);
	// 	}
	// 	printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
	// 	printf("PP_outfile: %d\n", (ppline)->pp_outfile);
	// 	printf("PP_infile: %d\n", (ppline)->pp_infile);
	// 	if ((ppline)->pp_outfile > 1)
	// 	{
	// 		dup2((ppline)->pp_outfile, STDOUT_FILENO);
	// 		close((ppline)->pp_outfile);
	// 		printf("PP_outfile closed\n");
	// 		printf("PP_outfile: %d\n", (ppline)->pp_outfile);
	// 	}
	// 	if ((ppline)->pp_infile > 1)
	// 	{
	// 		dup2((ppline)->pp_infile, STDIN_FILENO);
	// 		close((ppline)->pp_infile);
	// 		printf("PP_infile closed\n");
	// 		printf("PP_infile: %d\n", (ppline)->pp_infile);
	// 	}
	// 	execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
	// 	perror("Juliette erreur");
	// 	exit(-1); //EXIT_FAILURE
	// }
// 	return (0);
// }

// static void	dup_fd(int *stdin_dup, int *stdout_dup)
// {
// 	*stdin_dup = dup(0);
// 	if (*stdin_dup == -1)
// 		msg_error("dup", 0); //strerror(errno)
// 	*stdout_dup = dup(1);
// 	if (*stdout_dup == -1)
// 		msg_error("dup", 0); //strerror(errno)
// }

// static void	reinstall_fd(int stdin_dup, int stdout_dup)
// {
// 	if (dup2(stdin_dup, 0) == -1)
// 		msg_error("dup2", 0); //strerror(errno)
// 	if (dup2(stdout_dup, 0) == -1)
// 		msg_error("dup2", 0); //strerror(errno)
// }

// int	execute_single_builtin(t_ppline *ppline) //, char **mini_env_arr, char **cmd_path
// {
// 	// char	*cmd_path;
// 	int		exit_status;
// 	// int		stdin_dup;
// 	// int		stdout_dup;

// 	exit_status = 0;
// 	// cmd_path = NULL;
// 	// exit_code = 0;
// 	// printf(ORS "Execution builtin_red\n" RS);
// 	// printf("CMD: %s\n", (ppline)->pp_first_cmd);
// 	// if //(red_ptr->id == TOK_REDIR_OUT)
// 	// printf("PP_outfile: %d\n", (ppline)->pp_outfile);
// 	// printf("PP_infile: %d\n", (ppline)->pp_infile);

// 	printf(YELLOW "Execution single_builtin\n" RS);
// 	printf(YELLOW "pp_red_status: %d\n" RS, ppline->pp_red_status);
// 	// ppline->pp_builtin_status = 1;
// 	// dup_fd(&stdin_dup, &stdout_dup);
// 	// if (!ppline->ppline_cmd)
// 		exit_status = execute_builtin(&ppline);
// 	// if (ppline->pp_red_status == 0)
// 	// {
// 	// 	reinstall_fd(stdin_dup, stdout_dup);
// 	// 	return (1);
// 	// }
// 	// exit_status = execute_builtin(&ppline);
// 	// reinstall_fd(stdin_dup, stdout_dup);
// 	// ppline->pp_builtin_status = 0;
// 	printf(R "exit_status: %d\n" RS, exit_status);
// 	return (exit_status);
// }
	// if (ppline->pp_red_status == 1)
	// {

	// }
	// 	if (execute_builtin(&ppline) == -1) //->ppline_cmd[0], ppline->pp_list_env
	// 	{
	// 		printf("NOT builtin\n");
	// 		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
	// 		{
	// 			printf("NO PATH\n");
	// 			return (-1);
	// 		}
	// 		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
	// 				// execute_one_cmd(ppline, mini_env_arr, &cmd_path);
	// 	// execute_cmd(ppline, mini_env_arr); //return (execute_cmd(mini, &cmd, mini_env));
	// 		// execute_single_red(ppline, cmd_path);
	// 	}
	// }
	// if (check_if_builtin(ppline->pp_first_cmd))
	// {
	// 	printf("Builtin\n");
	// 	if ((ppline)->pp_outfile > 1)
	// 	{
	// 		dup2((ppline)->pp_outfile, STDOUT_FILENO);
	// 		close((ppline)->pp_outfile);
	// 		printf("PP_outfile closed\n");
	// 		printf("PP_outfile: %d\n", (ppline)->pp_outfile);
	// 	}
	// 	if ((ppline)->pp_infile > 1)
	// 	{
	// 		dup2((ppline)->pp_infile, STDIN_FILENO);
	// 		close((ppline)->pp_infile);
	// 		printf("PP_infile closed\n");
	// 		printf("PP_infile: %d\n", (ppline)->pp_infile);
	// 	}
	// 	// execute_builtin(&ppline); //->ppline_cmd[0], ppline->pp_list_env
	// 	// dup2((ppline)->pp_outfile, STDOUT_FILENO);
	// 	// close((ppline)->pp_outfile);
	// }
	// return (0);
	// else if (ppline->pp_red_status == 1)
	// 	execute_single_red(ppline, cmd_path);
	// else
	// 	execute_multi_cmd(ppline);
	// // else if (execve(cmd_path, ppline->ppline_cmd, ppline->pp_arr_env) == -1)
	// // 	msg_error(ft_strjoin(ppline->ppline_cmd[0], " : command not found\n"), 127);




// int	execute_single_cmd(t_ppline *ppline) //, char **mini_env_arr, char **cmd_path
// {
// 	char	*cmd_path;
// 	// int		exit_code;

// 	cmd_path = NULL;
// 	// exit_code = 0;
// 	printf(PURPLE "Execution single_cmd\n" RS);
// 	printf(PURPLE "Execution single_cmd pp_red_status: %d\n" RS, ppline->pp_red_status);
// 	if (ppline->pp_red_status == 0)
// 	{
// 		if (execute_builtin(&ppline) == -1) //->ppline_cmd[0], ppline->pp_list_env
// 		{
// 			printf("NOT builtin\n");
// 			if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
// 			{
// 				printf("NO PATH\n");
// 				return (-1);
// 			}
// 			printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
// 					// execute_one_cmd(ppline, mini_env_arr, &cmd_path);
// 		// execute_cmd(ppline, mini_env_arr); //return (execute_cmd(mini, &cmd, mini_env));
// 			// execute_single_red(ppline, cmd_path);
// 		}
// 	}
// 	else if (ppline->pp_red_status == 1)
// 		execute_single_red(ppline, cmd_path);
// 	else
// 		execute_multi_cmd(ppline);
// 	// else if (execve(cmd_path, ppline->ppline_cmd, ppline->pp_arr_env) == -1)
// 	// 	msg_error(ft_strjoin(ppline->ppline_cmd[0], " : command not found\n"), 127);
// 	return (0);
// }

// static int	execute_single_red(t_ppline *ppline, char *cmd_path) //
// {
// 	// char	*cmd_path;
// 	// // int		exit_code;

// 	// cmd_path = NULL;
// 	// (void)ppline;
// 	printf(GGREEN "Execution single_red\n" RS);
// 	printf("CMD: %s\n", (ppline)->pp_first_cmd);
// 	// if //(red_ptr->id == TOK_REDIR_OUT)

// 	if (check_if_builtin(ppline->pp_first_cmd)) //ppline->ppline_env //, ppline->pp_list_env) == -
// 	{
// 		if (is_builtin(&ppline->ppline_cmd[0], ppline->pp_list_env) == -1)
// 		{
// 	// dup2((ppline)->pp_outfile, STDOUT_FILENO);
// 	// close((ppline)->pp_outfile);
// 			printf("NOT builtin\n");
// 			// if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
// 			// {
// 			// 	printf("NO PATH\n");
// 			return (-1);
// 			// }
// 			// printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
// 		}
// 		printf("PP_outfile: %d\n", (ppline)->pp_outfile);
// 		dup2((ppline)->pp_outfile, STDOUT_FILENO);
// 		close((ppline)->pp_outfile);
// 		execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
// 		perror("Juliette erreur");
// 		exit(-1); //EXIT_FAILURE
// 	}
// 	return (0);
// }

// int	execute_single_cmd(t_ppline *ppline) //, char **mini_env_arr, char **cmd_path
// {
// 	char	*cmd_path;
// 	// int		exit_code;

// 	cmd_path = NULL;
// 	// exit_code = 0;
// 	printf(GGREEN "Execution single_cmd\n" RS);
// 	if (ppline->pp_red_status == 0)
// 	{
// 		if (is_builtin(&ppline->ppline_cmd[0], ppline->pp_list_env) == -1) //ppline->ppline_env
// 		{
// 			printf("NOT builtin\n");
// 			if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
// 			{
// 				printf("NO PATH\n");
// 				return (-1);
// 			}
// 			printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
// 			// execute_one_cmd(ppline, mini_env_arr, &cmd_path);
// 			// execute_cmd(ppline, mini_env_arr); //return (execute_cmd(mini, &cmd, mini_env));
// 			execute_single_red(ppline, cmd_path);
// 		}

// 	}
// 	else if (ppline->pp_red_status == 1)
// 		execute_single_red(ppline, cmd_path);
// 	else
// 		execute_multi_cmd(ppline);
// 	// else if (execve(cmd_path, ppline->ppline_cmd, ppline->pp_arr_env) == -1)
// 	// 	msg_error(ft_strjoin(ppline->ppline_cmd[0], " : command not found\n"), 127);
// 	return (0);
// }


// if (is_builtin(&ppline->ppline_cmd[0], mini_env) == -1) //ppline->ppline_env
	// 	{
	// 		printf("NOT builtin\n");
	// 		if (!(search_path(ppline, mini_env_arr, &cmd_path)))
	// 		{
	// 			printf("NO PATH\n");
	// 			return (-1);
	// 		}
	// 		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
	// 		// execute_one_cmd(ppline, mini_env_arr, &cmd_path);
	// 		execute_cmd(ppline, mini_env_arr); //return (execute_cmd(mini, &cmd, mini_env));
	// 	}

// static int	execute_single_red(t_ppline *ppline, char *cmd_path) //
// {
// 	// char	*cmd_path;
// 	// // int		exit_code;

// 	// cmd_path = NULL;
// 	// (void)ppline;
// 	printf(GGREEN "Execution single_red\n" RS);
// 	printf("CMD: %s\n", (ppline)->pp_first_cmd);
// 	// if //(red_ptr->id == TOK_REDIR_OUT)

// 	if (ft_builtin(ppline->pp_first_cmd))
// 	{
// 		printf("Builtin\n");
// 		// if ()
// 		dup2((ppline)->pp_outfile, STDOUT_FILENO);
// 		close((ppline)->pp_outfile);
// 		// is_builtin(&ppline->ppline_cmd[0], ppline->pp_list_env);
// 		// dup2((ppline)->pp_outfile, STDOUT_FILENO);
// 		// close((ppline)->pp_outfile);
// 	}
// 	else
// 	{
// 		printf("NOT builtin\n");
// 		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
// 		{
// 			printf("NO PATH\n");
// 			return (-1);
// 		}
// 		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
// 		printf("PP_outfile: %d\n", (ppline)->pp_outfile);
// 		dup2((ppline)->pp_outfile, STDOUT_FILENO);
// 		close((ppline)->pp_outfile);
// 		execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
// 		perror("Juliette erreur");
// 		exit(-1); //EXIT_FAILURE
// 	}
// 	return (0);
// }
