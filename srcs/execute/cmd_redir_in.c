#include "../../headers/minishell.h"

int ft_handle_redir_in(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	printf(LBLUE "\nredir_in\n\n");
	// (void)new_ppline;
	// (void)ptr_cmd_red;
	int	fd_in;
	int	i = 0;

	fd_in = 0;
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
		fd_in = open((*ptr_cmd_red)->next->content, O_RDONLY, 0777);
		if (!fd_in)
			msg_error("open file", errno);
	}
	// else
	// 	return (0);
	(*new_ppline)->pp_infile = fd_in;
	printf("FD pp_infile after open infile: %d\n\n" RS, (*new_ppline)->pp_infile);
	// dup2((*new_ppline)->pp_infile, STDIN_FILENO);
	// close((*new_ppline)->pp_infile);
	// execve((*new_ppline)->pp_first_cmd, (*new_ppline)->ppline_cmd, (*new_ppline)->ppline_env);
	// perror("Juliette erreur");
	// exit(-1); //EXIT_FAILURE
	return (1);
}
