#include "../../headers/minishell.h"

int ft_handle_redir_append(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	printf(LBLUE "\nredir_append\n\n");
	// (void)ptr_cmd_red;
	// (void)new_ppline;
	int	fd_out;
	int	i = 0;

	fd_out = 0;
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
		fd_out = open((*ptr_cmd_red)->next->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (!fd_out)
			msg_error("open file", errno);
	}
	// else
	// 	return (0);
	(*new_ppline)->pp_outfile = fd_out;	
		// close((*new_ppline)->pp_outfile);
		// dup2((*new_ppline)->pp_outfile, STDOUT_FILENO);
		// execve((*new_ppline)->pp_first_cmd, (*new_ppline)->ppline_cmd, (*new_ppline)->ppline_env);
		// perror("Juliette erreur");
		// exit(-1); //EXIT_FAILURE
	printf("FD pp_outfile after open outfile: %d\n", (*new_ppline)->pp_infile);
	return (1);
}
