#include "../../headers/minishell.h"

int ft_handle_redir_append(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	printf(LBLUE "\nredir_append\n\n");
	// (void)ptr_cmd_red;
	// (void)new_ppline;
	int	fd_out;
	int	i = 0;

	fd_out = -1;
	printf("(*ptr_cmd_red)->id: %d\n", (*ptr_cmd_red)->id);
	if ((*ptr_cmd_red)->id == TOK_REDIR_OUT_APPEND)
	{
		printf("CMD: %s\n", (*new_ppline)->pp_first_cmd);
		printf("Command arguments:\n");
		while ((*new_ppline)->ppline_cmd[i] != NULL)
		{
			printf("%s\n", (*new_ppline)->ppline_cmd[i]);
			i++;
		}
		// Check if the file already exists and has write permissions
		if (access((*ptr_cmd_red)->next->content, F_OK) == 0)
		{
			if (access((*ptr_cmd_red)->next->content, W_OK) != 0)
			{
				// File exists but doesn't have write permissions
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
				msg_error("Permission denied", errno);
				return 0;
			}
		}

		fd_out = open((*ptr_cmd_red)->next->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd_out == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
			msg_error("Error opening file", errno);
		}
	}
	// else
	// 	return (0);
	(*new_ppline)->pp_fd_out = fd_out;	
		// close((*new_ppline)->pp_outfile);
		// dup2((*new_ppline)->pp_outfile, STDOUT_FILENO);
		// execve((*new_ppline)->pp_first_cmd, (*new_ppline)->ppline_cmd, (*new_ppline)->ppline_env);
		// perror("Juliette erreur");
		// exit(-1); //EXIT_FAILURE
	printf("FD pp_fd_out after open outfile: %d\n", (*new_ppline)->pp_fd_out);
	return (1);
}
