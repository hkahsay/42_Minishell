#include "../../headers/minishell.h"

static t_cmd	*parse_commands(t_token **tok_head, int cmd_num)
{
	t_token	*tok_h;
	t_token	**tok_cmd_list;
	t_cmd	*cmd_list;
	int		i;

	tok_h = *tok_head;
	i = 0;
	tok_cmd_list = my_malloc(sizeof(t_token *) * (cmd_num + 1));
	if (!tok_cmd_list)
		return (0);
	tok_cmd_list[cmd_num] = 0;
	while (tok_h && i < cmd_num)
	{
		tok_cmd_list[i] = tok_h;
		while (tok_h->next && tok_h->id != TOK_PIPE)
		{
			tok_h = tok_h->next;
			if (tok_h->id == TOK_PIPE)
				break ;
		}
		if (tok_h->id == TOK_PIPE)
			tok_h = tok_h->next;
		i++;
	}
	cmd_list = build_cmd_list(tok_cmd_list);
	my_free(tok_cmd_list);
	return (cmd_list);
}

void	*parse(t_token **token_head, t_envnode *mini_env)
{
	int		cmd_num;
	t_cmd	*cmd_list;

	cmd_num = ft_count_pipes(token_head) + 1;
	cmd_list = parse_commands(token_head, cmd_num);
	if (!cmd_list)
		return (0);
	free_token_list(*token_head);
	printf("STDOUT: %d\n", STDOUT_FILENO);
	execute(cmd_list, cmd_num, mini_env);
	return (0);
}
