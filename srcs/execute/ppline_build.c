#include "../../headers/minishell.h"

void	free_ppline(t_ppline **new_ppline, int *i)
{
	for (int j = 0; j < *i; j++)
		my_free((*new_ppline)->ppline_cmd[j]);
	my_free((*new_ppline)->ppline_cmd);
	my_free((*new_ppline));
	// return (0);
}

t_ppline	*build_ppline_array(t_cmd **cmd_head, int cmd_n, t_envnode *mini_env)
{
	t_ppline	*ppline = NULL;
	t_ppline	*new_ppline = NULL;
	t_ppline	*ppline_tail = NULL;
	t_cmd		*cmd_ptr = *cmd_head;
	int			pp_idx;

	pp_idx = cmd_n;
	while (cmd_ptr != NULL && cmd_n > 0)
	{
		new_ppline = ft_new_ppline();
		if (new_ppline == NULL)
			return NULL;
		new_ppline->pp_arr_env = ft_mini_env_array(mini_env, ft_mini_env_size(mini_env)); // env_size
		new_ppline->pp_list_env = mini_env;
		new_ppline->ppline_idx = pp_idx;
		if (cmd_ptr->cmd_word)
			ft_handle_word(&new_ppline, cmd_ptr->cmd_word);
		if (cmd_ptr->cmd_red)
		{
			if (ft_handle_redir_all(&new_ppline, cmd_ptr->cmd_red))
				new_ppline->pp_red_status = 1;
		}
		if (ppline == NULL)
		{
			ppline = new_ppline;
			ppline_tail = new_ppline;
		}
		else
		{
			ppline_tail->next = new_ppline;
			ppline_tail = new_ppline;
		}
		cmd_ptr = cmd_ptr->next;
		cmd_n--;
	}
	return (ppline);
}
