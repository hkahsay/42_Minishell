#include "../../headers/minishell.h"

int ft_handle_redir_out(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	int	fd_out;

	fd_out = 0;
	if ((*ptr_cmd_red)->id == TOK_REDIR_OUT)
	{
		if (access((*ptr_cmd_red)->next->content, F_OK) == 0)
		{
			if (access((*ptr_cmd_red)->next->content, W_OK) != 0)
			{
				ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
				ft_putstr_fd((*ptr_cmd_red)->next->content, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				return (0);
			}
		}
		fd_out = open((*ptr_cmd_red)->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_out == -1)
			return (-1);
	}
	(*new_ppline)->pp_fd_out = fd_out;
	return (1);
}
