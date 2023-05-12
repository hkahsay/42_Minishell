#include "../../headers/minishell.h"

static int	handle_redir(t_ppl *new_ppl, t_token *cmd_red)
{
	if (ft_handle_redir_all(&new_ppl, cmd_red) == 1)
	{
		new_ppl->pp_red_status = 1;
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

static void	append_ppl(t_ppl **ppl, t_ppl *new_ppl, \
t_ppl **ppl_tail)
{
	if (*ppl == NULL)
	{
		*ppl = new_ppl;
		*ppl_tail = new_ppl;
	}
	else
	{
		(*ppl_tail)->next = new_ppl;
		*ppl_tail = new_ppl;
	}
}

static void	fill_env_ppl(t_ppl *ppl, t_envnode *mini_env, int pp_idx)
{
	ppl->pp_arr_env = mini_env_arr(mini_env, mini_env_size(mini_env));
	ppl->pp_list_env = mini_env;
	ppl->ppl_idx = pp_idx;
}

t_ppl	*build_ppl(t_cmd **cmd_head, int cmd_n, t_envnode *mini_env)
{
	t_ppl	*ppl;
	t_ppl	*new_ppl;
	t_ppl	*ppl_tail;
	t_cmd	*cmd_ptr;
	int		pp_idx;

	pp_idx = cmd_n;
	cmd_ptr = *cmd_head;
	ppl = NULL;
	new_ppl = NULL;
	ppl_tail = NULL;
	while (cmd_ptr != NULL && cmd_n-- > -1)
	{
		new_ppl = ft_new_ppl();
		if (new_ppl == NULL)
			return (NULL);
		fill_env_ppl(new_ppl, mini_env, pp_idx);
		if (cmd_ptr->cmd_word)
			ft_handle_word(&new_ppl, cmd_ptr->cmd_word);
		if (cmd_ptr->cmd_red)
		{
			if (!handle_redir(new_ppl, cmd_ptr->cmd_red))
				return (NULL);
		}
		append_ppl(&ppl, new_ppl, &ppl_tail);
		cmd_ptr = cmd_ptr->next;
	}
	return (ppl);
}
