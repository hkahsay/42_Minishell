#include "../../headers/minishell.h"

void	free_ppline(t_ppline **new_ppline, int *i)
{
	printf("%p\n", &((*new_ppline)->pp_first_cmd));
	my_free((*new_ppline)->pp_first_cmd);
	for (int j = 0; j < *i; j++)
		my_free((*new_ppline)->ppline_cmd[j]);
	my_free((*new_ppline)->ppline_cmd);
	my_free((*new_ppline));
	// return (0);
}

void	free_one_ppline(t_ppline **new_ppline)
{
	printf("%p\n", &((*new_ppline)->pp_first_cmd));
	my_free((*new_ppline)->pp_first_cmd);
	my_free((*new_ppline)->ppline_cmd[0]);
	my_free((*new_ppline)->ppline_cmd);
	my_free((*new_ppline));
	// return (0);
}

// static t_ppline *build_ppline_list(t_ppline **ppline, t_ppline *new_ppline)
// {
// 	// t_ppline	*ppline = NULL;
// 	t_ppline	*ppline_tail = NULL;
// 	printf("4new_pppline init\n");

// 	printf(R"cmd: %s\n"RS, new_ppline->pp_first_cmd);
// 	if ((*ppline) == NULL)
// 	{
// 		printf("5new_pppline init\n");
// 		(*ppline) = (new_ppline);
// 		ppline_tail = (new_ppline);
// 	}
// 	else
// 	{
// 		printf("6new_pppline init\n");
// 		ppline_tail->next = (new_ppline);
// 		ppline_tail = (new_ppline);
// 	}
// 	printf("7new_pppline init\n");
// 	return ((*ppline));
// }

static void append_ppline(t_ppline **ppline, t_ppline *new_ppline, t_ppline **ppline_tail)
{
    if (*ppline == NULL)
    {
        *ppline = new_ppline;
        *ppline_tail = new_ppline;
    }
    else
    {
        (*ppline_tail)->next = new_ppline;
        *ppline_tail = new_ppline;
    }
}

static int handle_redirection(t_ppline *new_ppline, t_token *cmd_red)
{
	if (ft_handle_redir_all(&new_ppline, cmd_red) == 1)
	{
		new_ppline->pp_red_status = 1;
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
		ft_putstr_fd(cmd_red->next->content, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (0);
	}
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
			return (NULL);
		new_ppline->pp_arr_env = ft_mini_env_array(mini_env, ft_mini_env_size(mini_env)); // env_size
		new_ppline->pp_list_env = mini_env;
		new_ppline->ppline_idx = pp_idx;
		if (cmd_ptr->cmd_word)
			ft_handle_word(&new_ppline, cmd_ptr->cmd_word);
		if (cmd_ptr->cmd_red)
		{
			if (!handle_redirection(new_ppline, cmd_ptr->cmd_red))
                return NULL;
			// if (ft_handle_redir_all(&new_ppline, cmd_ptr->cmd_red) == 1)
			// 	new_ppline->pp_red_status = 1;
			// else
			// {
			// 	ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
			// 	ft_putstr_fd(cmd_ptr->cmd_red->next->content, STDERR_FILENO);
			// 	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			// 	return (NULL);
			// }
		}
		append_ppline(&ppline, new_ppline, &ppline_tail);
		cmd_ptr = cmd_ptr->next;
		cmd_n--;
	}
	return (ppline);
}

