#include "../../headers/minishell.h"

int ft_handle_redir_in(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	int	fd_in;

	fd_in = 0;
	printf(R"create redir_in\n" RS);
	printf(LB"create redir_in: (*new_ppline)->pp_fd_in: %d\n"RS, (*new_ppline)->pp_fd_in);
	printf(LB"create redir_in: (*new_ppline)->pp_fd_out: %d\n"RS, (*new_ppline)->pp_fd_out);
	if ((*ptr_cmd_red)->id == TOK_REDIR_IN)
	{
		printf(R"create redir_in access\n" RS);
		if (access((*ptr_cmd_red)->next->content, R_OK) != 0 && errno != ENOENT)
		{
			printf("access in\n");
			// File exists but does not have read permissions
			ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
			ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (0);
		}
		else
		{
			fd_in = open((*ptr_cmd_red)->next->content, O_RDONLY);
			printf(LB"create redir_in: file name: %s\n"RS, (*ptr_cmd_red)->next->content);
			if (fd_in == -1)
				return (-1);
		}
	}
	(*new_ppline)->pp_fd_in = fd_in;
	printf(LB"create redir_in: (*new_ppline)->pp_fd_in: %d\n"RS, (*new_ppline)->pp_fd_in);
	return (1);
}
