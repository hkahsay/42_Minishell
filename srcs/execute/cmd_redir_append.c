#include "../../headers/minishell.h"

void	*ft_handle_redir_append(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	(void)ptr_cmd_red;
	(void)new_ppline;
	printf(LBLUE "\nredir_append\n\n");
		// (void)ptr_cmd_red;
	// (void)new_ppline;
	int	fd_out;

	fd_out = -1;
	printf("(*ptr_cmd_red)->id: %d\n", (*ptr_cmd_red)->id);
	if ((*ptr_cmd_red)->id == TOK_REDIR_OUT_APPEND)
	{
		printf("Content: %s\n", (*ptr_cmd_red)->next->content);
		fd_out = open((*ptr_cmd_red)->next->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
		(*new_ppline)->pp_outfile = fd_out;
		if ((*new_ppline)->pp_outfile < 0)
		{
			perror("open");
			exit(1); //EXIT_FAILURE
		}
		printf("PP_outfile: %d\n", (*new_ppline)->pp_outfile);
		printf("CMD: %s\n", (*new_ppline)->pp_first_cmd);
		// close((*new_ppline)->pp_outfile);
		// dup2((*new_ppline)->pp_outfile, STDOUT_FILENO);
		// execve((*new_ppline)->pp_first_cmd, (*new_ppline)->ppline_cmd, (*new_ppline)->ppline_env);
		// perror("Juliette erreur");
		// exit(-1); //EXIT_FAILURE
	}
	return (0);
}
