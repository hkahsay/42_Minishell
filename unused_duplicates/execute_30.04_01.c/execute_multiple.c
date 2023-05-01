#include "../../headers/minishell.h"

int	execute_path_cmd(t_ppline *ppline)
{
	char	*cmd_path;
	//pid_t	kid_pid;
	// char	*msg;
// 	int		exit_status;

	cmd_path = NULL;
	printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
	printf(PURPLE "Execute cmd\n" RS);
	// kid_pid = fork();
	// printf(PURPLE "kid_pid after fork: %d\n" RS, kid_pid);
	// if (kid_pid == 0)
	// {
		printf("process\n");
		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
		{
			g_exit_status = 127;
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			msg_error(ft_strjoin(ppline->pp_first_cmd, ": command not found"), errno);
			// printf(R "NO PATH\n" RS);
			// return (-1);
		}
		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
		// int i = 0;
		// printf(PURPLE "(ppline)->ppline_cmd: \n" RS);
		// while ((ppline)->ppline_cmd[i] != NULL)
		// {
		// 	printf("%s\n", (ppline)->ppline_cmd[i]);
		// 	i++;
		// }
		// printf(PURPLE "(ppline)->pp_arr_env: \n" RS);
		// print_mini_env_array((ppline)->pp_arr_env);
		if (!execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env))
			msg_error("error execution: ", errno);
		// exit(-1); //EXIT_FAILURE
		//printf(PURPLE "kid_pid after kid: %d\n" RS, kid_pid);
	// }
	// else
	// {
	// 	waitpid(kid_pid, &(ppline->pp_exit), 0);
	// 	printf(PURPLE "kid_pid after waitpid: %d\n" RS, kid_pid);
	// }
	// if (WIFEXITED(ppline->pp_exit))
	// {
	// 	printf(PURPLE "ppline->pp_exit waitpid: %d\n" RS, ppline->pp_exit);
	// 	g_exit_status = WEXITSTATUS(ppline->pp_exit);
	// 	// return (0);
	// }
	// close_fds(&ppline);
	return (1); //1
	// exit(0);
}

int	execute_multi_cmd(t_ppline *ppline) //, char **mini_env_arr
{
	printf(GGREEN "Execution multi cmd\n" RS);
	t_ppline	*pp_curr;
	int			num_pipes = 0;

	pp_curr = ppline;

	init_pipe(&pp_curr, &num_pipes);
	printf(GGREEN "Execution multi cmd: Retour after init_pipe\n" RS);
	if (num_pipes == 0)
	{
		execute_path_cmd(pp_curr);
		// execute_kid(pp_curr);
		// exit(0);
	}
	while (pp_curr) // && num_pipes > 0
	{
		printf(GGREEN "Execution multi cmd: Enter while loop\n" RS);
		if (pp_curr->pp_infile < 0 || pp_curr->pp_outfile < 0)
		{
			pp_curr = pp_curr->next;
			continue ;
		}
		pp_curr->pp_pid = fork();
		if (pp_curr->pp_pid == -1)
			msg_error("error redir: ", errno);
		if (pp_curr->pp_pid == 0) //child
		{
			execute_kid(pp_curr);
			printf("Execution multi cmd: Came back after execute_kid\n");
			exit(0);
		}
		wait_execution(&pp_curr);
		pp_curr = pp_curr->next;
	}
	// wait_execution(&pp_curr);
	printf("Execution multi cmd: before wait_execution\n");
	printf("Execution multi cmd: after wait_execution\n");
	return (EXIT_SUCCESS);
}