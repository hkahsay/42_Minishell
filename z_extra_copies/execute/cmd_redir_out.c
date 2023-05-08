#include "../../headers/minishell.h"

int ft_handle_redir_out(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	printf(LBLUE "\nredir_out\n\n");
	int	fd_out;
	int	i = 0;

	fd_out = -1;
	if ((*ptr_cmd_red)->id == TOK_REDIR_OUT)
	{
		printf("CMD: %s\n", (*new_ppline)->pp_first_cmd);
		printf("Command arguments:\n");
		while ((*new_ppline)->ppline_cmd[i] != NULL)
		{
			printf("%s\n", (*new_ppline)->ppline_cmd[i]);
			i++;
		}
		printf("Outfile name: %s\n", (*ptr_cmd_red)->next->content);
		// Check if the file already exists and has write permissions
		if (access((*ptr_cmd_red)->next->content, F_OK) == 0)
		{
			// File exists
			if (access((*ptr_cmd_red)->next->content, W_OK) != 0)
			{
				// File does not have write permissions
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
				msg_error("Permission denied", errno);  // Use your error function
				// msg_error("Permission denied", 1);  // Use your error function
				return (0);
			}
		}
		fd_out = open((*ptr_cmd_red)->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		printf("FD pp_outfile after open outfile: %d\n", fd_out);
		if (fd_out == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
			msg_error("Permission denied", errno);
		}
	}
	// else
	// 	return (0);
	(*new_ppline)->pp_fd_out = fd_out;
	//  close((*new_ppline)->pp_outfile);
	printf("FD pp_fd_out after open outfile: %d\n", (*new_ppline)->pp_fd_out);
	return (1);
}
		// printf("PP_outfile: %d\n", (*new_ppline)->pp_outfile);
		// printf("CMD: %s\n", (*new_ppline)->pp_first_cmd);
		// dup2((*new_ppline)->pp_outfile, STDOUT_FILENO);
		// close((*new_ppline)->pp_outfile);

	// (void)ptr_cmd_red;
	// (void)new_ppline;
		// dup2((*new_ppline)->pp_outfile, STDOUT_FILENO);
		// execve((*new_ppline)->pp_first_cmd, (*new_ppline)->ppline_cmd, (*new_ppline)->ppline_env);
		// perror("Juliette erreur");
		// exit(-1); //EXIT_FAILURE
