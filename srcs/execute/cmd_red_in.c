#include "../../headers/minishell.h"

int	ft_handle_redir_in(t_ppl **new_ppl, t_token **ptr_cmd_red)
{
	int	fd_in;

	fd_in = 0;
	if ((*ptr_cmd_red)->id == T_RI)
	{
		if (access((*ptr_cmd_red)->next->content, R_OK) != 0 && errno != ENOENT)
		{
			printf(GREEN "1error\n" RS);

			ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
			ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (0);
		}
		else
		{
			fd_in = open((*ptr_cmd_red)->next->content, O_RDONLY);
			printf("fd_in %d\n", fd_in);
			if (fd_in == -1)
				return (-1);
		}
	}
	(*new_ppl)->pp_fd_in = fd_in;
	return (1);
}
