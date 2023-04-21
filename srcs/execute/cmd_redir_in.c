#include "../../headers/minishell.h"

void	*ft_handle_redir_in(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	(void)new_ppline;
	(void)ptr_cmd_red;
	printf(LBLUE "\nredir_in\n\n");
		// (void)ptr_cmd_red;
	// (void)new_ppline;
	printf(LBLUE "\nredir_out\n\n");
	int	fd_in;

	fd_in = -1;
	if ((*ptr_cmd_red)->id == TOK_REDIR_IN)
	{
		printf("Content: %s\n", (*ptr_cmd_red)->next->content);
		fd_in = open((*ptr_cmd_red)->next->content, O_RDONLY | O_CREAT | O_TRUNC, 0644);
		(*new_ppline)->pp_infile = fd_in;
		if ((*new_ppline)->pp_infile < 0)
		{
			perror("open");
			exit(1); //EXIT_FAILURE
		}
		printf("PP_infile: %d\n", (*new_ppline)->pp_infile);
		printf("CMD: %s\n", (*new_ppline)->pp_first_cmd);
		// close((*new_ppline)->pp_outfile);
		// dup2((*new_ppline)->pp_outfile, STDOUT_FILENO);
		// execve((*new_ppline)->pp_first_cmd, (*new_ppline)->ppline_cmd, (*new_ppline)->ppline_env);
		// perror("Juliette erreur");
		// exit(-1); //EXIT_FAILURE
	}
	return (0);
}
