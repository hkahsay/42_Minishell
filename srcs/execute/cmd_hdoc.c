#include "../../headers/minishell.h"

void	*ft_handle_heredoc(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	(void)ptr_cmd_red;
	(void)new_ppline;
	printf(LBLUE "\nheredoc\n\n");
	return (0);
}
