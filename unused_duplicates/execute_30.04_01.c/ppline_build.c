#include "../../headers/minishell.h"

void	free_ppline(t_ppline **new_ppline, int *i)
{
	for (int j = 0; j < *i; j++)
		free((*new_ppline)->ppline_cmd[j]);
	free((*new_ppline)->ppline_cmd);
	free((*new_ppline));
	// return (0);
}

t_ppline	*build_ppline_array(t_cmd **cmd_head, int cmd_n, t_envnode *mini_env)
{
	printf(OL "\nbuild_ppline_array\n");
	t_ppline	*ppline = NULL;
	t_ppline	*new_ppline = NULL;
	t_ppline	*ppline_tail = NULL;
	t_cmd		*cmd_ptr = *cmd_head;
	// t_token		*word_ptr;
	int			pp_idx;
	// int			env_size = 0;

	// word_ptr = cmd_ptr->cmd_word;
	pp_idx = cmd_n;
	// printf(R "cmd_n: %d\n" RS, cmd_n);
	// env_size = ft_mini_env_size(mini_env);
	// printf(R "env_size: %d\n", env_size);
	while (cmd_ptr != NULL && cmd_n > 0)
	{
		new_ppline = ft_new_ppline();
		if (new_ppline == NULL)
			return NULL;
		new_ppline->pp_arr_env = ft_mini_env_array(mini_env, ft_mini_env_size(mini_env)); // env_size
		// print_mini_env_array(new_ppline->pp_arr_env);
		new_ppline->pp_list_env = mini_env;
		// print_mini_envp(mini_env);
		new_ppline->ppline_idx = pp_idx;
		if (cmd_ptr->cmd_word)
		{
			printf(OL "build_ppline_array: cmd_word\n");
			ft_handle_word(&new_ppline, cmd_ptr->cmd_word);
		}
		if (cmd_ptr->cmd_red)
		{
			printf(OL "build_ppline_array: redir_all\n");
			if (ft_handle_redir_all(&new_ppline, cmd_ptr->cmd_red))
				new_ppline->pp_red_status = 1;
		}
		printf(OL "\nbuild_ppline list\n\n");
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
	printf(BMAG "BUILT PPLINE: printing ppline_list\n");
	print_ppline_list(ppline, new_ppline->ppline_idx);
	printf(RS);
	return (ppline);
}
