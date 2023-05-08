#include "../../headers/minishell.h"

int ft_handle_redir_in(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	printf(LBLUE "\nredir_in\n\n");
	// (void)new_ppline;
	// (void)ptr_cmd_red;
	int	fd_in;
	int	i = 0;

	fd_in = -1;
	if ((*ptr_cmd_red)->id == TOK_REDIR_IN)
	{
		printf("CMD: %s\n", (*new_ppline)->pp_first_cmd);
		printf("Command arguments:\n");
		while ((*new_ppline)->ppline_cmd[i] != NULL)
		{
			printf("%s\n", (*new_ppline)->ppline_cmd[i]);
			i++;
		}
		printf("Infile name: %s\n", (*ptr_cmd_red)->next->content);
		if (access((*ptr_cmd_red)->next->content, F_OK) != 0)
		{
			// File does not exist
			fd_in = open((*ptr_cmd_red)->next->content, O_RDONLY | O_CREAT, 0644);
			if (fd_in == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
				msg_error("Permission denied", errno);  // Use your error function
				// msg_error("Permission denied", 1);  // Use your error function
				return (0);
			}
		}
		else if (access((*ptr_cmd_red)->next->content, R_OK) != 0)
		{
			// File exists but does not have read permissions
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
			msg_error("Permission denied", errno);  // Use your error function
			// msg_error("Permission denied", 1);  // Use your error function
			return (0);
		}
		else
		{
			fd_in = open((*ptr_cmd_red)->next->content, O_RDONLY);
			if (fd_in == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
				msg_error("Permission denied", errno);  // Use your error function
				// msg_error("Permission denied", 1);  // Use your error function
				return (0);
			}
		}
	}
	// else
	// 	return (0);
	(*new_ppline)->pp_fd_in = fd_in;
	printf("FD pp_infile after open infile: %d\n\n" RS, (*new_ppline)->pp_fd_in);
	// dup2((*new_ppline)->pp_infile, STDIN_FILENO);
	// close((*new_ppline)->pp_infile);
	// execve((*new_ppline)->pp_first_cmd, (*new_ppline)->ppline_cmd, (*new_ppline)->ppline_env);
	// perror("Juliette erreur");
	// exit(-1); //EXIT_FAILURE
	return (1);
}
