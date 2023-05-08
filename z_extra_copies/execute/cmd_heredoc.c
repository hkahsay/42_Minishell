#include "../../headers/minishell.h"

/* int fd_heredoc[2];
  pipe(fd_heredoc)
while (1)
  * {
	  char * line = readline (">")
	if (strcmp(line, keyword))
	   break
	write (fd_heredoc[1], line, strlen(line)))


  }
 *
 */

int	ft_handle_heredoc(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	// int		fd[2];
	// char	*line;
	if ((*ptr_cmd_red)->content == NULL)
		return (0);
	// printf("Heredoc EOF (*ptr_cmd_red)->content: %s\n" RS, (*ptr_cmd_red)->next->content);
	(*new_ppline)->pp_heredoc_eof = ft_strdup((*ptr_cmd_red)->next->content);
	printf("Heredoc EOF (*new_ppline)->pp_heredoc_eof: %s\n" RS, (*new_ppline)->pp_heredoc_eof);
	// pipe(fd);
	// while (1)
	// {
	// 	line = readline("> ");

	// 	if (line == NULL || !(ft_strcmp((*new_ppline)->pp_heredoc_eof, line)))
	// 		break ;
	// 	ft_putendl_fd(line, fd[1]);
	// }
	// close(fd[1]);
	// (*new_ppline)->pp_fd_in = fd[0];
	// // close(fd[0]);
	// printf("FD pp_fd_in after heredoc: %d\n" RS, (*new_ppline)->pp_fd_in);
	// printf("FD pp_fd_out after heredoc: %d\n" RS, (*new_ppline)->pp_fd_out);

	return (1);
}

// int ft_handle_heredoc(t_ppline **new_ppline, t_token **ptr_cmd_red)
// {
// 	printf(LBLUE "\nredir_heredoc\n\n");
// 	// int	fd_out;
// 	int	i = 0;

// 	// fd_out = -1;
// 	if ((*ptr_cmd_red)->id == TOK_HEREDOC)
// 	{
// 		// printf("CMD: %s\n", (*new_ppline)->pp_first_cmd);
// 		// printf("Command arguments:\n");
// 		// while ((*new_ppline)->ppline_cmd[i] != NULL)
// 		// {
// 		// 	printf("%s\n", (*new_ppline)->ppline_cmd[i]);
// 		// 	i++;
// 		// }
// 		printf("Heredoc EOF: %s\n", (*ptr_cmd_red)->next->content);
// 		// fd_out = open((*ptr_cmd_red)->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 		// if (!fd_out)
// 		// 	msg_error("open file", errno);
// 	}
// 	// else
// 	// 	return (0);
// 	// (*new_ppline)->pp_outfile = fd_out;
// 	// printf("FD pp_outfile after open outfile: %d\n", (*new_ppline)->pp_outfile);
// 	return (1);
// }
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

