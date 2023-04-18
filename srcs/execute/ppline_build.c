#include "../../headers/minishell.h"

void	free_ppline(t_ppline **new_ppline, int *i)
{
	for (int j = 0; j < *i; j++)
		free((*new_ppline)->ppline_cmd[j]);
	free((*new_ppline)->ppline_cmd);
	free((*new_ppline));
	// return (0);
}

t_ppline	*build_ppline_array(t_cmd **cmd_head, int cmd_n, char	**mini_env_arr)
{
	t_ppline	*ppline = NULL;
	t_ppline	*new_ppline = NULL;
	t_ppline	*ppline_tail = NULL;
	t_cmd		*cmd_ptr = *cmd_head;
	t_token		*word_ptr;

	word_ptr = cmd_ptr->cmd_word;

	// printf(R "cmd_n: %d\n" RS, cmd_n);
	while (cmd_ptr != NULL)
	{
		new_ppline = ft_new_ppline();
		if (new_ppline == NULL)
			return NULL;
		new_ppline->ppline_env = mini_env_arr;
		if (cmd_ptr->cmd_word)
		{
			ft_handle_word(&new_ppline, cmd_ptr->cmd_word);
		}
		if (cmd_ptr->cmd_red)
		{
			if (ft_handle_redir_all(&new_ppline, cmd_ptr->cmd_red))
				new_ppline->red_status = 1;
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
	}
	printf(BMAG "BUILT PPLINE: printing ppline_list\n");
	print_ppline_list(ppline, cmd_n);
	printf(RS);
	return (ppline);
}
