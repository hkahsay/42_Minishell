#include "../../headers/minishell.h"

int ft_handle_redir_in(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	int	fd_in;

	fd_in = 0;
	if ((*ptr_cmd_red)->id == TOK_REDIR_IN)
	{
		if (access((*ptr_cmd_red)->next->content, R_OK) != 0 && errno != ENOENT)
		{
			ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
			ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (0);
		}
		else
		{
			fd_in = open((*ptr_cmd_red)->next->content, O_RDONLY);
			printf("FD fd_in after open infile: %d\n\n" RS, fd_in);
			if (fd_in == -1)
			{
				printf(GREEN "error\n" RS);
				return (-1);
			}
		}
		
	}
	(*new_ppline)->pp_fd_in = fd_in;
	printf("FD pp_infile after open infile: %d\n\n" RS, (*new_ppline)->pp_fd_in);
	return (1);
}
