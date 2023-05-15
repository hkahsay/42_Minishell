#include "../../headers/minishell.h"

int	execute_heredoc(t_ppl **ppl)
{
	int		fd[2];
	char	*line;

	line = NULL;
	if (pipe(fd) == -1)
		msg_error("minishell_VH: failed to create pipe", errno);
	(*ppl)->saved_stdin = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp((*ppl)->pp_heredoc_eof, line) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (EXIT_SUCCESS);
}
