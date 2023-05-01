#include "../../headers/minishell.h"

int ft_handle_heredoc(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	printf(LBLUE "\nredir_heredoc\n\n");
	// int	fd_out;
	int	i = 0;

	// fd_out = -1;
	if ((*ptr_cmd_red)->id == TOK_HEREDOC)
	{
		printf("CMD: %s\n", (*new_ppline)->pp_first_cmd);
		printf("Command arguments:\n");
		while ((*new_ppline)->ppline_cmd[i] != NULL)
		{
			printf("%s\n", (*new_ppline)->ppline_cmd[i]);
			i++;
		}
		printf("Heredoc EOF: %s\n", (*ptr_cmd_red)->next->content);
		// fd_out = open((*ptr_cmd_red)->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		// if (!fd_out)
		// 	msg_error("open file", errno);
	}
	// else
	// 	return (0);
	// (*new_ppline)->pp_outfile = fd_out;
	// printf("FD pp_outfile after open outfile: %d\n", (*new_ppline)->pp_outfile);
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


    // Execute heredoc input in a shell

