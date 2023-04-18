#include "../../headers/minishell.h"

void	*ft_handle_redir_in(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	(void)new_ppline;
	printf(LBLUE "\nredir_in\n\n");
	int	fd_out;

	fd_out = -1;
	if ((*ptr_cmd_red)->id == TOK_REDIR_IN)
	{
		fd_out = open((*ptr_cmd_red)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		(*new_ppline)->outfile = fd_out;
		if ((*new_ppline)->outfile < 0)
		{
			perror("open");
			exit(-1); //EXIT_FAILURE
		}
		dup2((*new_ppline)->outfile, STDOUT_FILENO);
		close((*new_ppline)->outfile);
		execve((*new_ppline)->pp_first_cmd, (*new_ppline)->ppline_cmd, (*new_ppline)->ppline_env);
		perror("execve");
		exit(-1); //EXIT_FAILURE
	}
	return (0);
}
