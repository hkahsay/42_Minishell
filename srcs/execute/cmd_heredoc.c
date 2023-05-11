#include "../../headers/minishell.h"

int	ft_handle_heredoc(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	if ((*ptr_cmd_red)->content == NULL)
		return (0);
	(*new_ppline)->pp_heredoc_eof = ft_strdup((*ptr_cmd_red)->next->content);
	return (1);
}
